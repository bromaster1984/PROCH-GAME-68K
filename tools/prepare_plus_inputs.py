#!/usr/bin/env python3
"""Prepare user-provided ROM/system copies; never download or distribute them."""
import hashlib
import json
from pathlib import Path
import struct
import sys


def checksum_dc42(payload):
    value = 0
    if len(payload) % 2:
        raise ValueError('Odd DiskCopy payload length')
    for word, in struct.iter_unpack('>H', payload):
        value = (value + word) & 0xffffffff
        value = (value >> 1) | ((value & 1) << 31)
    return value


def prepare(inputs, output, application=None):
    inputs, output = Path(inputs), Path(output)
    rom = (inputs/'Mac-Plus.ROM').read_bytes()
    raw = rom[:131072]
    if len(raw) != 131072 or struct.unpack_from('>I', raw)[0] != 0x4d1f8172:
        raise ValueError('Expected user-provided Macintosh Plus v3 ROM')
    if sum(struct.unpack('>65534H', raw[4:])) != 0x4d1f8172:
        raise ValueError('ROM checksum mismatch')
    image = (inputs/'MacOS_6.0.8_System_Startup.img').read_bytes()
    if len(image) < 84 or image[82:84] != b'\x01\x00':
        raise ValueError('Expected DiskCopy 4.2 image')
    size, tags, expected = struct.unpack_from('>III', image, 64)
    if len(image) != 84 + size + tags:
        raise ValueError('Truncated DiskCopy image')
    disk = image[84:84+size]
    if checksum_dc42(disk) != expected or disk[1024:1026] != b'BD':
        raise ValueError('Disk checksum mismatch or not HFS')
    output.mkdir(parents=True, exist_ok=True)
    for name, data in [('vMac.ROM',raw),('System608.dsk',disk)]:
        path = output/name
        if path.exists() and path.read_bytes() != data:
            raise ValueError(f'Preserve existing modified test disk: {path}; choose a new output directory')
        path.write_bytes(data)
    report = {'model':'Plus', 'ram_bytes':4194304, 'rom_checksum':'4d1f8172',
              'rom_ignored_trailer_bytes':len(rom)-len(raw),
              'rom_sha256':hashlib.sha256(raw).hexdigest(),
              'dc42_checksum':f'{expected:08x}', 'system_sha256':hashlib.sha256(disk).hexdigest()}
    if application is not None:
        from check_artifacts import check
        application=Path(application)
        check(application)
        for name in ['PROCH.bin','PROCH.dsk']:
            data=(application/name).read_bytes()
            target=output/name
            if target.exists() and target.read_bytes()!=data:
                raise ValueError('Preserve existing application test image; choose a new output directory')
            target.write_bytes(data)
        report['application_sha256']=hashlib.sha256((output/'PROCH.bin').read_bytes()).hexdigest()
        report['application_dsk_sha256']=hashlib.sha256((output/'PROCH.dsk').read_bytes()).hexdigest()
    (output/'inputs.json').write_text(json.dumps(report,indent=2)+'\n')
    return report


if __name__ == '__main__':
    print(json.dumps(prepare(sys.argv[1],sys.argv[2],sys.argv[3] if len(sys.argv)>3 else None),indent=2))
