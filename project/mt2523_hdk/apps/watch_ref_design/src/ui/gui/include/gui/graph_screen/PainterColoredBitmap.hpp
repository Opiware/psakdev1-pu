/* Copyright Statement:
 *
 */

#ifndef PAINTERCOLOREDBITMAP_HPP
#define PAINTERCOLOREDBITMAP_HPP

#include <stdint.h>
#if !defined(USE_BPP) || USE_BPP==16
#include <touchgfx/widgets/canvas/PainterRGB565Bitmap.hpp>
#elif USE_BPP==24
#include <touchgfx/widgets/canvas/PainterRGB888Bitmap.hpp>
#endif

using namespace touchgfx;

/**
 * @class PainterColoredBitmap PainterColoredBitmap.hpp gui/graph_screen/PainterColoredBitmap.hpp
 *
 * @brief A Painter that will paint using a bitmap with a given color.
 *
 *        PainterColoredBitmap will take the color for a given point from a bitmap. The pixel
 *        from the bitmap is 'multiplied' with the given color. This means that if the given
 *        color is red (255,0,0), the blue and green parts of the image will be masked out.
 *        Interesting effects can be obtained if the given image contains colors from the
 *        entire spectrum, but usually the bitmap will be a gray scale bitmap and in this case
 *        the painter can be used to get various shades of the selected color.
 *
 * @see AbstractPainter */
class PainterColoredBitmap :
#if !defined(USE_BPP) || USE_BPP==16
    public PainterRGB565Bitmap
#elif USE_BPP==24
    public PainterRGB888Bitmap
#endif
{
public:
    /**
     * @fn PainterColoredBitmap::PainterColoredBitmap();
     *
     * @brief Default constructor.
     *
     *        Default constructor.
     */
    PainterColoredBitmap();

    /**
     * @fn PainterColoredBitmap::PainterColoredBitmap(colortype color, const Bitmap& bmp = Bitmap(BITMAP_INVALID), uint8_t alpha = 255);
     *
     * @brief Constructor.
     *
     *        Constructor.
     *
     * @param color The color.
     * @param bmp   The bitmap.
     * @param alpha the alpha.
     */
    PainterColoredBitmap(colortype color, const Bitmap &bmp = Bitmap(BITMAP_INVALID), uint8_t alpha = 255);

    /**
     * @fn void PainterColoredBitmap::setColor(colortype color);
     *
     * @brief Sets color and alpha to use when drawing the CanvasWidget.
     *
     *        Sets color and alpha to use when drawing the CanvasWidget.
     *
     * @param color The color.
     *
     * ### param alpha (Optional) The alpha.
     */
    void setColor(colortype color);

protected:

    /**
     * @fn virtual bool renderNext(uint16_t& pixelRed, uint8_t& pixelGreen, uint8_t& pixelBlue, uint8_t& pixelAlpha);
     *
     * @brief Gets the color and alpha for the next pixel.
     *
     *        Gets the color and alpha for the next pixel.
     *
     * @param [out] pixelRed   The red.
     * @param [out] pixelGreen The green.
     * @param [out] pixelBlue  The blue.
     * @param [out] pixelAlpha The alpha.
     *
     * @return true if it succeeds, false if it fails.
     */
    virtual bool renderNext(uint8_t &pixelRed, uint8_t &pixelGreen, uint8_t &pixelBlue, uint8_t &pixelAlpha);

    uint8_t red;   ///< The red part of the color
    uint8_t green; ///< The green part of the color
    uint8_t blue;  ///< The blue part of the color
};

#endif /* PAINTERCOLOREDBITMAP_HPP */
