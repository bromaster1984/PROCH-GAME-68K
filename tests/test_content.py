import importlib.util
from pathlib import Path
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location('content', ROOT/'tools/generate_content.py')
content = importlib.util.module_from_spec(spec)
spec.loader.exec_module(content)


class ContentTests(unittest.TestCase):
    def test_complete_encoding(self):
        self.assertEqual(content.encode(content.POLISH), bytes(range(0x80,0x92)))
        self.assertEqual(content.encode('„Żyję”…'), b'"\x90yj\x85"...')

    def test_no_silent_substitution(self):
        with self.assertRaises(ValueError): content.encode('Nieznany: Ω')

    def test_every_glyph_and_polish_difference(self):
        chars, rows = content.glyphs()
        self.assertEqual(len(chars), 113)
        for c,base in zip(content.POLISH, 'AaCcEeLlNnOoSsZzZz'):
            self.assertNotEqual(rows[c], rows[base], c)
        self.assertNotEqual(rows['Ź'], rows['Ż'])

    def test_generation_is_deterministic(self):
        with tempfile.TemporaryDirectory() as a, tempfile.TemporaryDirectory() as b:
            content.generate(a); content.generate(b)
            for name in ['content.h','font.h','font.pbm','font-mask.pbm']:
                self.assertEqual((Path(a)/name).read_bytes(),(Path(b)/name).read_bytes())


if __name__ == '__main__': unittest.main()
