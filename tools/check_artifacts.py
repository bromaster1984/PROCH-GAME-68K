#!/usr/bin/env python3
"""Validate forks, resource map and partition sizes; not an SE runtime test."""
import binascii
import hashlib
import json
import struct
import sys
from pathlib import Path


def require(condition, message):
    if not condition:
        raise ValueError(message)


def resources(fork):
    require(len(fork) >= 16, 'truncated resource header')
    data, mapping, data_len, map_len = struct.unpack_from('>4I', fork)
    require(data >= 16 and mapping >= data + data_len, 'overlapping fork areas')
    require(data + data_len <= len(fork) and mapping + map_len <= len(fork),
            'resource fork areas outside file')
    require(map_len >= 30, 'truncated resource map')
    types_offset, names_offset = struct.unpack_from('>HH', fork, mapping + 24)
    require(28 <= types_offset < map_len and names_offset <= map_len, 'bad map offsets')
    types = mapping + types_offset
    type_count = struct.unpack_from('>H', fork, types)[0] + 1
    require(types_offset + 2 + 8 * type_count <= map_len, 'truncated type table')
    result = {}
    for index in range(type_count):
        pos = types + 2 + 8 * index
        kind, count, refs = struct.unpack_from('>4sHH', fork, pos)
        require(types_offset + refs + (count + 1) * 12 <= map_len, 'truncated reference list')
        for j in range(count + 1):
            ref = types + refs + j * 12
            rid = struct.unpack_from('>h', fork, ref)[0]
            offset = int.from_bytes(fork[ref + 5:ref + 8], 'big')
            require(offset + 4 <= data_len, 'resource offset outside data area')
            size = struct.unpack_from('>I', fork, data + offset)[0]
            require(offset + 4 + size <= data_len, 'truncated resource payload')
            key = (kind, rid)
            require(key not in result, 'duplicate resource ID')
            result[key] = fork[data + offset + 4:data + offset + 4 + size]
    return result


def macbinary(blob):
    require(len(blob) >= 128 and blob[0] == 0 and 1 <= blob[1] <= 63, 'invalid MacBinary')
    require(blob[65:73] == b'APPLPRCH', 'wrong Finder type/creator')
    require(int.from_bytes(blob[124:126], 'big') == binascii.crc_hqx(blob[:124], 0),
            'MacBinary header CRC mismatch')
    data_len, rsrc_len = struct.unpack_from('>II', blob, 83)
    require(rsrc_len > 0, 'missing resource fork')
    start = 128 + ((data_len + 127) // 128) * 128
    require(start + rsrc_len <= len(blob), 'truncated MacBinary forks')
    table = resources(blob[start:start + rsrc_len])
    require((b'CODE', 0) in table and (b'CODE', 1) in table, 'missing 68K CODE resources')
    require(len(table[b'CODE', 0]) >= 16 and len(table[b'CODE', 1]) > 4, 'empty code')
    require((b'SIZE', -1) in table and len(table[b'SIZE', -1]) == 10, 'missing SIZE')
    flags, preferred, minimum = struct.unpack('>HII', table[b'SIZE', -1])
    require((preferred, minimum) == (2048 * 1024, 1536 * 1024), 'wrong memory partition')
    return {'bytes': len(blob), 'data_fork_bytes': data_len, 'resource_fork_bytes': rsrc_len,
            'resources': [k.decode('ascii') + ':' + str(i) for k, i in sorted(table)],
            'preferred_partition': preferred, 'minimum_partition': minimum,
            'sha256': hashlib.sha256(blob).hexdigest()}


def check(directory):
    directory = Path(directory)
    result = macbinary((directory / 'PROCH.bin').read_bytes())
    disk = (directory / 'PROCH.dsk').read_bytes()
    require(len(disk) >= 1536 and disk[1024:1026] == b'BD', 'not a raw HFS volume')
    result['hfs_bytes'] = len(disk)
    result['hfs_sha256'] = hashlib.sha256(disk).hexdigest()
    result['scope'] = 'container integrity only; not SE compatibility'
    return result


if __name__ == '__main__':
    print(json.dumps(check(sys.argv[1] if len(sys.argv) > 1 else 'dist'), indent=2))
