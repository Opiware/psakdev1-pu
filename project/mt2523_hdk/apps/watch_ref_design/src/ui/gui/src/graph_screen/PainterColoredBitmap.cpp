/* Copyright Statement:
 *
 */

#include <gui/graph_screen/PainterColoredBitmap.hpp>
#include <touchgfx/Color.hpp>

using namespace touchgfx;

PainterColoredBitmap::PainterColoredBitmap()
{
    setColor(0);
    setBitmap(Bitmap(BITMAP_INVALID));
    setAlpha(255);
}

PainterColoredBitmap::PainterColoredBitmap(colortype color, const Bitmap &bmp, uint8_t alpha)
{
    setColor(color);
    setBitmap(bmp);
    setAlpha(alpha);
}

void PainterColoredBitmap::setColor(colortype color)
{
    red = Color::getRedColor(color);
    green = Color::getGreenColor(color);
    blue = Color::getBlueColor(color);
}

bool PainterColoredBitmap::renderNext(uint8_t &pixelRed, uint8_t &pixelGreen, uint8_t &pixelBlue, uint8_t &pixelAlpha)
{
    // Get RGBA from the bitmap
#if !defined(USE_BPP) || USE_BPP==16
    if (PainterRGB565Bitmap::renderNext(pixelRed, pixelGreen, pixelBlue, pixelAlpha))
#elif USE_BPP==24
    if (PainterRGB888Bitmap::renderNext(pixelRed, pixelGreen, pixelBlue, pixelAlpha))
#endif
    {
        // Multiply with our color
        pixelRed   = (pixelRed   * this->red) / 255;
        pixelGreen = (pixelGreen * this->green) / 255;
        pixelBlue  = (pixelBlue  * this->blue) / 255;
        return true;
    }
    return false;
}
