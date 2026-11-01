import importlib.util
import struct
import os
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
ARTIFACTS = Path(os.environ.get('PROCH_ARTIFACT_DIR', str(ROOT/'dist')))
spec = importlib.util.spec_from_file_location('artifacts', ROOT / 'tools/check_artifacts.py')
artifacts = importlib.util.module_from_spec(spec)
spec.loader.exec_module(artifacts)


class ArtifactChecks(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.blob = (ARTIFACTS / 'PROCH.bin').read_bytes()

    def test_generated_application_has_forks_and_partition(self):
        result = artifacts.macbinary(self.blob)
        self.assertIn('CODE:1', result['resources'])
        self.assertEqual(result['minimum_partition'], 1536 * 1024)

    def test_corrupt_header_is_rejected(self):
        b = bytearray(self.blob)
        b[10] ^= 1
        with self.assertRaisesRegex(ValueError, 'CRC'):
            artifacts.macbinary(b)

    def test_truncated_resource_fork_is_rejected(self):
        size = struct.unpack_from('>I', self.blob, 87)[0]
        with self.assertRaisesRegex(ValueError, 'truncated'):
            artifacts.macbinary(self.blob[:128 + size - 1])

    def test_resource_offset_outside_fork_is_rejected(self):
        b = bytearray(self.blob[128:])
        struct.pack_into('>I', b, 4, 0xffffffff)
        with self.assertRaises(ValueError):
            artifacts.resources(b)

    def test_current_hfs_volume_header(self):
        result = artifacts.check(ARTIFACTS)
        self.assertGreater(result['hfs_bytes'], result['bytes'])


if __name__ == '__main__':
    unittest.main()
