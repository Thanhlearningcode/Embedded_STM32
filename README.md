
# STM32F411VET6 LED Blinking Project

## Giới thiệu

Đây là project mẫu cho **STM32F411VET6** sử dụng **GCC toolchain** trên Linux để nháy LED trên board.
Code viết bằng C, sử dụng **CMSIS** và startup code chuẩn của STMicroelectronics.

---

## Cấu trúc thư mục

```
STM32F411VET6-Blink/
├── CMSIS/               # Thư viện CMSIS chuẩn
├── Inc/                 # File header (.h)
├── Src/                 # File nguồn (.c)
├── Startup/             # Startup assembly (.s) và linker script (.ld)
└── build/               # Output file: .elf, .bin, object, map files
```

---

## Về CMSIS (Cortex Microcontroller Software Interface Standard)

CMSIS là bộ thư viện chuẩn do ARM phát triển nhằm chuẩn hóa giao diện lập trình cho các vi điều khiển Cortex-M.
Nó cung cấp các file header, định nghĩa register, cấu trúc dữ liệu và hàm API cơ bản giúp bạn viết code dễ dàng hơn, không cần viết trực tiếp các giá trị hex cho các thanh ghi.

Trong project STM32F411VET6, CMSIS sẽ bao gồm các file như:

* `core_cm4.h` - định nghĩa vi xử lý Cortex-M4
* `system_stm32f4xx.c/h` - cấu hình hệ thống (clock, vector table)
* `stm32f411xe.h` - định nghĩa register của STM32F411xE

### Lấy CMSIS cho STM32F4

Bạn có thể tải bộ CMSIS chuẩn từ:

* Trang chính thức của ARM:
  [https://developer.arm.com/tools-and-software/embedded/cmsis](https://developer.arm.com/tools-and-software/embedded/cmsis)
* Hoặc tải từ **STM32CubeF4** package của ST:
  [https://www.st.com/en/embedded-software/stm32cubef4.html](https://www.st.com/en/embedded-software/stm32cubef4.html)

Thư mục `CMSIS/` trong project sẽ gồm:

```
CMSIS/
├── Device/
│   └── ST/
│       └── STM32F4xx/
│           ├── Include/           # File header định nghĩa STM32F4, startup
│           └── Source/            # System configuration
├── Core/
    ├── Include/                  # Cortex-M core headers (core_cm4.h, ...)
```

---

## Yêu cầu cài đặt

* GCC ARM Embedded Toolchain (`arm-none-eabi-gcc`)
* `make`
* OpenOCD (để flash và debug)
* stlink-tools (`st-flash`)

Cài nhanh trên Ubuntu/Debian:

```bash
sudo apt update
sudo apt install gcc-arm-none-eabi gdb-multiarch make openocd stlink-tools
```

---

## Build project

```bash
make
```

File output: `build/STM32F411.bin`, `build/STM32F411.elf`.

---

## Nạp code vào STM32

```bash
make flash
```

Hoặc thủ công:

```bash
st-flash write build/STM32F411.bin 0x8000000
```

---

## Debug với OpenOCD và GDB

1. Chạy OpenOCD:

```bash
openocd -f interface/stlink.cfg -f target/stm32f4x.cfg
```

2. Mở terminal khác chạy GDB:

```bash
arm-none-eabi-gdb build/STM32F411.elf
```

3. Trong GDB:

![image](https://github.com/user-attachments/assets/5f37c46f-06b0-4d48-b82d-f12add0c7cb2)

```gdb
target remote localhost:3333
load
break main
continue
```

---

## Tham khảo

* [CMSIS Documentation](https://arm-software.github.io/CMSIS_5/Core/html/index.html)
* [STM32CubeF4 HAL libraries](https://www.st.com/en/embedded-software/stm32cubef4.html)
* [STM32F4 Reference Manual (PDF)](https://www.st.com/resource/en/reference_manual/dm00031020-stm32f405-415-stm32f407-417-stm32f427-437-and-stm32f429-439-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)

---

**Chúc bạn thành công với STM32F411VET6!** 🚀

---

