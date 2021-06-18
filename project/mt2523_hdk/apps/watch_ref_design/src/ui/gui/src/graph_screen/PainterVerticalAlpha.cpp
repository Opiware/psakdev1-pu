/* Copyright Statement:
 *
 */

#include <gui/graph_screen/PainterVerticalAlpha.hpp>
#include <touchgfx/Color.hpp>

using namespace touchgfx;

PainterVerticalAlpha::PainterVerticalAlpha(colortype color /*= 0*/, int alpha0atY /*= 100*/)
{
    setColor(color, alpha0atY);
}

void PainterVerticalAlpha::setColor(colortype color, int alphaZeroAt)
{
    red = Color::getRedColor(color);
    green = Color::getGreenColor(color);
    blue = Color::getBlueColor(color);
    alpha0atY = alphaZeroAt;
}

bool PainterVerticalAlpha::renderInit()
{
    int gradientAlpha = 255 - (currentY * 255 / alpha0atY);
    if (gradientAlpha < 0) {
        gradientAlpha = 0;
    }
    if (gradientAlpha > 255) {
        gradientAlpha = 255;
    }
    alpha = gradientAlpha;
    return true;
}

bool PainterVerticalAlpha::renderNext(uint8_t &pixelRed, uint8_t &pixelGreen, uint8_t &pixelBlue, uint8_t &pixelAlpha)
{
    pixelRed = this->red;
    pixelGreen = this->green;
    pixelBlue = this->blue;
    pixelAlpha = this->alpha;
    return true;
}

void PainterVerticalAlpha::renderPixel(uint16_t *p, uint8_t pixelRed, uint8_t pixelGreen, uint8_t pixelBlue)
{
#if !defined(USE_BPP) || USE_BPP==16
#define fastrand(g_seed) ((214013*(uint32_t)(g_seed)+2531011)>>16)
    uint8_t rand = fastrand((currentX + *p) * (currentY + *p));

    if (pixelRed   < 0xF8) {
        pixelRed   = pixelRed   + ((rand >> 5));    // Add bit 7-5 of rand to red to get rounding
    }
    if (pixelGreen < 0xFC) {
        pixelGreen = pixelGreen + ((rand >> 3) & 0x3);    // Add bit 4-3 of rand to green to get rounding
    }
    if (pixelBlue  < 0xF8) {
        pixelBlue  = pixelBlue  + ((rand) & 0x7);    // Add bit 2-0 of rand to blue to get rounding
    }

    AbstractPainterRGB565::renderPixel(p, pixelRed, pixelGreen, pixelBlue);
#elif USE_BPP==24
    AbstractPainterRGB888::renderPixel(p, pixelRed, pixelGreen, pixelBlue);
#endif
}
