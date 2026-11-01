/* Native Toolbox bring-up, stage 1. Not a finished game or production artwork. */
#include <Quickdraw.h>
#include <Windows.h>
#include <Menus.h>
#include <Fonts.h>
#include <TextEdit.h>
#include <Dialogs.h>
#include <Events.h>
#include <Files.h>
#include <Memory.h>
#include <stdlib.h>
#include <string.h>
#include "render_1bit.h"

static WindowPtr window;
static ProchBitmap pixels;
static BitMap bitmap;
#ifndef PROCH_AUTOTEST
static uint8_t alternate;
static uint8_t running = 1;
#endif
static uint16_t clicks;
static const Rect scene = {39, 6, 247, 366};

static void text(short x, short y, const char *s)
{
    MoveTo(x, y);
    DrawText((Ptr)s, 0, (short)strlen(s));
}

static void draw(void)
{
    Rect r;
    SetPort(window);
    EraseRect(&window->portRect);
    TextFont(0);
    TextSize(9);
    SetRect(&r, 4, 23, 368, 249); FrameRect(&r);
    text(8, 34, "PROCH - test natywny 68000 / 1-bit");
    CopyBits(&bitmap, &window->portBits, &bitmap.bounds, &scene, srcCopy, NULL);
    SetRect(&r, 372, 23, 508, 125); FrameRect(&r);
    text(378, 42, "Etap 1: Toolbox");
    text(378, 58, "360 x 208");
    text(378, 74, "rowBytes = 46");
    text(378, 90, "9568 bajtow");
    text(378, 111, clicks ? "Mysz: klik odebrany" : "Kliknij wzor");
    SetRect(&r, 4, 253, 508, 296); FrameRect(&r);
    text(9, 267, "Wzor testowy, nie ilustracja gry. Klik zmienia fragment bitmapy.");
    text(9, 281, "Plik: wzor / wyjscie. Command-Q konczy. Bez wersji WWW.");
}

static void click(Point global)
{
    Rect dirty;
    Point local = global;
    SetPort(window);
    GlobalToLocal(&local);
    if (!PtInRect(local, &scene)) return;
    proch_invert(&pixels, local.h - scene.left, local.v - scene.top);
    ++clicks;
    /* Retain changes in the buffer, so update events restore the same image. */
    SetRect(&dirty, local.h - 3, local.v - 3, local.h + 4, local.v + 4);
    SectRect(&dirty, &scene, &dirty);
    InvalRect(&dirty);
    SetRect(&dirty, 378, 98, 506, 118);
    InvalRect(&dirty);
}

#ifndef PROCH_AUTOTEST
static void command(long selection)
{
    if ((selection >> 16) == 128) {
        if ((selection & 0xffff) == 1) {
            alternate = !alternate;
            proch_pattern(&pixels, alternate);
            InvalRect(&scene);
        } else if ((selection & 0xffff) == 3) running = 0;
    }
    HiliteMenu(0);
}
#endif

#ifdef PROCH_AUTOTEST
static OSErr test_file(ConstStringPtr name, const void *data, long bytes)
{
    short ref;
    OSErr error = FSOpen(name, 0, &ref);
    long written = bytes;
    if (error != noErr) {
        error = Create(name, 0, 'PRCH', 'TEXT');
        if (error == noErr) error = FSOpen(name, 0, &ref);
    }
    if (error != noErr) return error;
    error = SetEOF(ref, 0);
    if (error == noErr) error = FSWrite(ref, &written, data);
    if (written != bytes) error = ioErr;
    if (FSClose(ref) != noErr) error = ioErr;
    return error;
}

static OSErr screenshot(void)
{
    /* Capture the actual 1-bit QuickDraw framebuffer, with no host reconstruction. */
    static const char header[] = "P4\n512 342\n";
    short ref;
    long bytes = 512L / 8 * 342;
    OSErr error;
    if ((qd.screenBits.rowBytes & 0x3fff) != 64) return paramErr;
    error = test_file((ConstStringPtr)"\pSCREEN.PBM", header, sizeof(header) - 1);
    if (error != noErr) return error;
    error = FSOpen((ConstStringPtr)"\pSCREEN.PBM", 0, &ref);
    if (error != noErr) return error;
    error = SetFPos(ref, fsFromLEOF, 0);
    if (error == noErr) error = FSWrite(ref, &bytes, qd.screenBits.baseAddr);
    if (bytes != 21888) error = ioErr;
    if (FSClose(ref) != noErr) error = ioErr;
    return error;
}

/* Test-only executable. Run through LaunchAPPL to read the `out` data fork. */
static int smoke(void)
{
    OSErr error;
    Point p;
    const char *result;
    uint8_t ok;
    draw();
    ok = window != NULL && window->portRect.right == 512 &&
         window->portRect.bottom == 342 && bitmap.rowBytes == 46;
    ok = ok && !GetPixel(6, 39) && GetPixel(7, 39);
    ok = ok && screenshot() == noErr;
    SetPt(&p, 7, 39); LocalToGlobal(&p); click(p); draw();
    ok = ok && clicks == 1 && !GetPixel(7, 39);
    result = ok ? "PROCH_TOOLBOX_SMOKE_PASS\n" : "PROCH_TOOLBOX_SMOKE_FAIL\n";
    error = test_file((ConstStringPtr)"\pout", result, (long)strlen(result));
    FlushVol(NULL, 0);
    return ok && error == noErr ? 0 : 1;
}
#endif

int main(void)
{
    Rect bounds;
    MenuHandle menu;
    MaxApplZone();
    InitGraf(&qd.thePort); InitFonts(); InitWindows(); InitMenus();
    TEInit(); InitDialogs(NULL); InitCursor();
    menu = NewMenu(128, (ConstStringPtr)"\pPlik");
    AppendMenu(menu, (ConstStringPtr)"\pZmien wzor;-;Wyjscie/Q");
    InsertMenu(menu, 0); DrawMenuBar();
    /* The System menu bar uses global y=0..19. The content uses y=20..341. */
    SetRect(&bounds, 0, 20, 512, 342);
    window = NewWindow(NULL, &bounds, (ConstStringPtr)"\pPROCH", true, plainDBox,
                       (WindowPtr)-1L, false, 0);
    if (window == NULL) return 1;
    SetPort(window);
    SetOrigin(0, 20); /* Use the specification's global coordinates throughout. */
    bitmap.baseAddr = (Ptr)pixels.words;
    bitmap.rowBytes = PROCH_STRIDE;
    SetRect(&bitmap.bounds, 0, 0, PROCH_WIDTH, PROCH_HEIGHT);
    proch_pattern(&pixels, 0);
    InvalRect(&window->portRect);
#ifdef PROCH_AUTOTEST
    {
        int result = smoke();
        DisposeWindow(window);
        return result;
    }
#else
    while (running) {
        EventRecord e;
        WindowPtr hit;
        /* Sleep/yield between events. Render only when invalidated. */
        if (!WaitNextEvent(everyEvent, &e, 6, NULL)) continue;
        switch (e.what) {
            case updateEvt:
                if ((WindowPtr)e.message == window) {
                    BeginUpdate(window); draw(); EndUpdate(window);
                }
                break;
            case mouseDown:
                switch (FindWindow(e.where, &hit)) {
                    case inMenuBar: command(MenuSelect(e.where)); break;
                    case inContent:
                        if (hit == window) { SelectWindow(window); click(e.where); }
                        break;
                }
                break;
            case keyDown:
                if (e.modifiers & cmdKey) command(MenuKey(e.message & charCodeMask));
                break;
        }
    }
    DisposeWindow(window);
    return 0;
#endif
}
