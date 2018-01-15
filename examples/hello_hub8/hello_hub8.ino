#include <font8x16basic.h>
#include <idwrhub8.h>

idwrhub8 hub8(9,6,7,14,15);

void setup() {
  hub8.hardware_spi_init(10);
  hub8.pilihfont(font8x16basic);
}

void loop() {
  hub8.teks_hub("indoware");
  hub8.display_dmd_hub8();

}
