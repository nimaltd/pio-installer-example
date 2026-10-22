# lib-installer-example-pio

A small library made to try [lib-installer](https://github.com/nimaltd/lib-installer) on, and a starting point for making your own library installable into a PlatformIO project.

It does one useful thing. `example_due()` says yes once every `EXAMPLE_PERIOD_MS` milliseconds and never blocks, so a loop can blink an LED, read a sensor or print a line on a rhythm without sleeping. `example_hello()` writes `EXAMPLE_GREETING` and a count into a line for you to print. Both settings are in `example_config.h`. Its `uptime` option adds `example_uptime()`, the time since start up in hours, minutes and seconds.

It reads no clock of its own: you give it the time with every call, from `millis()`, `HAL_GetTick()` or a count of your own. So it builds with every framework PlatformIO has, and with none at all on the native platform, where it runs on your computer.

It also has a step for the installer to run, so you can see one work: `make-id` makes `include/example_id.h`, the board's own ID, a random number. The installer shows what it runs and asks first. Its script, `tools/make_id.py`, comes into your project's folder as the library's own.

---

## Try the installer with it

Install the installer once:

```bash
pip install lib-installer
```

It needs lib-installer 3.0.0 or newer. `pip install --upgrade lib-installer` brings an older one up to date.

No board is needed. Make a folder for a project, and in it a `platformio.ini` for PlatformIO's native platform, which builds a program for your computer:

```ini
[env:native]
platform = native
```

Then, from that folder:

```bash
lib-installer nimaltd/lib-installer-example-pio
```

Press Enter at its questions, and the library goes into `lib/example/`, with a `library.json` the installer writes for it. Last, it asks about its step:

```
Run
  make-id      Make this board's own ID, include/example_id.h
               python tools/make_id.py include/example_id.h
               Run it? [Y/n]:
Made include/example_id.h: device 4A49F7A1.
               done
```

Enter runs it. Then put this in `src/main.c`:

```c
#include <stdio.h>
#include "example.h"

int main(void)
{
    example_t tick;
    char      line[40];
    uint32_t  now;

    example_init(&tick, 0U);

    /* Two seconds, ten milliseconds at a time: the time is whatever it is given. */
    for (now = 0U; now <= 2000U; now += 10U)
    {
        if (example_due(&tick, now))
        {
            printf("%s\n", example_hello(&tick, line, sizeof(line)));
        }
    }

    return 0;
}
```

Build it and run it:

```bash
pio run -e native -t exec
```

```
Hello from example 1
Hello from example 2
Hello from example 3
Hello from example 4
```

### On a board

The same library, in a project for a board, with the time from the framework's own clock. With Arduino:

```cpp
#include <Arduino.h>
#include "example.h"

example_t tick;

void setup()
{
    Serial.begin(115200);
    example_init(&tick, millis());
}

void loop()
{
    char line[40];

    if (example_due(&tick, millis()))
    {
        Serial.println(example_hello(&tick, line, sizeof(line)));
    }
}
```

With STM32Cube, give it `HAL_GetTick()`. With ESP-IDF, `(uint32_t)(esp_timer_get_time() / 1000)`. Several environments in one `platformio.ini`, one for each board, all build the one copy in `lib/`.

### Things to try

**Print the board's ID.** `include/example_id.h` is in the project's `include` folder, which PlatformIO puts on the include path of your `src/`:

```c
#include "example_id.h"     /* made by the make-id step, this board's own */

printf("device %08lX\n", (unsigned long)EXAMPLE_DEVICE_ID);
```

```
device 4A49F7A1
```

Run the install again, and the step is not asked about: `make-id skipped, include/example_id.h is already there`, so the ID never changes under a board already in use. Delete the file, and the next install asks again. `--run make-id` runs it without asking, `--no-run make-id` leaves it, and `--yes` takes every answer offered, for a script. Nobody to answer, and it is not run.

**Keep a setting through an update.** Open `lib/example/src/example_config.h`, and change the period between its `USER CODE` lines:

```c
/* USER CODE BEGIN EXAMPLE_CONFIGURATION */
#define EXAMPLE_PERIOD_MS           250U
#define EXAMPLE_GREETING            "Hi"
/* USER CODE END EXAMPLE_CONFIGURATION */
```

Run the install command again: every file is replaced, and your settings are still there. The program now says `Hi` eight times in its two seconds.

**Add a part, and take it out.** `--with uptime` adds `example_uptime.h` and `example_uptime.c`, and their source to `library.json`. `--without uptime` takes them out again.

```bash
lib-installer nimaltd/lib-installer-example-pio --with uptime
```

```c
#include "example_uptime.h"

example_uptime_t up = example_uptime(millis());   /* up.hours, up.minutes, up.seconds */
```

**Uninstall it.** Its files go, and its `library.json`. A configuration header with your settings in it is saved beside them first, as a `.bak`. `tools/make_id.py` goes with them, and `include/example_id.h` stays, since it is yours:

```bash
lib-installer --uninstall example
```

**Without internet.** Download this repository as a zip, from the green **Code** button, **Download ZIP**, and give the installer the zip instead of the name:

```bash
lib-installer D:/Downloads/lib-installer-example-pio-main.zip
```

---

## Make your own library installable

Copy [`installer.yml`](installer.yml) to the root of your library's repository, and change what is yours: its name, its description, its repository, its files, and the `pio` part that `library.json` is written from. Every key the installer reads is in it, with a comment saying what it does; the ones this library has no use for are commented out. Only `name` and `files` are required.

Then anyone installs your library with:

```bash
lib-installer yourname/yourlibrary
```

Name the header to include first in `files`, list the frameworks and platforms it really builds with, and put `extern "C"` in every header of C code, as this one has, for a project in C++. `run` lists the steps run after the install, with the script in [`tools/make_id.py`](tools/make_id.py). The [lib-installer README](https://github.com/nimaltd/lib-installer#for-someone-writing-a-library) has the rest.

---

## API

| Function | What it does |
|---|---|
| `void example_init(example_t *handle, uint32_t now_ms)` | Start a period of `EXAMPLE_PERIOD_MS` from `now_ms` |
| `bool example_due(example_t *handle, uint32_t now_ms)` | Whether the period has passed by `now_ms`. Returns at once, and starts the next one when it has |
| `uint32_t example_count(const example_t *handle)` | How many times `example_due()` has said yes |
| `const char *example_hello(const example_t *handle, char *text, size_t size)` | Write `EXAMPLE_GREETING` and the count into `text`, and return it, for `printf()` or `Serial.println()` |
| `example_uptime_t example_uptime(uint32_t now_ms)` | With the `uptime` option: `now_ms`, the time since start up, in hours, minutes and seconds |

Declare one `example_t` for each thing that repeats on its own rhythm, and give every call the time from the same clock, in milliseconds. A loop that comes back late is caught up, so the rhythm does not drift.

---

## License

Apache License 2.0. See [LICENSE.md](LICENSE.md).
