import json
import unittest
from pathlib import Path

from PIL import Image


ROOT = Path(__file__).resolve().parents[1]


class SceneArtTests(unittest.TestCase):
    def test_production_bitmaps_match_sources_and_hotspots(self):
        scenes = json.loads((ROOT / 'scenes.json').read_text())
        for number in (33, 34):
            with self.subTest(scene=number):
                name = f'L{number}'
                image = Image.open(ROOT / 'bg' / f'{name}.png')
                self.assertEqual(image.size, (360, 208))
                self.assertEqual(image.mode, '1')
                self.assertEqual(len(image.getcolors()), 2)
                raw = image.tobytes()
                packed = b''.join(
                    bytes(byte ^ 0xff for byte in raw[y * 45:(y + 1) * 45]) + b'\0'
                    for y in range(208)
                )
                self.assertEqual((ROOT / 'art' / 'packed' / f'{name}.bin').read_bytes(), packed)
                for hotspot in scenes[number - 1]['hotspots']:
                    crop = image.crop(tuple(hotspot['rect']))
                    black = crop.convert('L').histogram()[0]
                    # At least some clear ink and some white space in each target.
                    self.assertGreater(black, 50, hotspot['id'])
                    self.assertLess(black, crop.width * crop.height * 0.95, hotspot['id'])


if __name__ == '__main__':
    unittest.main()
