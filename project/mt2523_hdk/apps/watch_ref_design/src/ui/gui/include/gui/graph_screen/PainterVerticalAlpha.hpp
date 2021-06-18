/* Copyright Statement:
 *
 */

#ifndef PAINTERVERTICALALPHA_HPP
#define PAINTERVERTICALALPHA_HPP

#include <touchgfx/hal/Types.hpp>
#include <stdint.h>
#if !defined(USE_BPP) || USE_BPP==16
#include <touchgfx/widgets/canvas/AbstractPainterRGB565.hpp>
#elif USE_BPP==24
#include <touchgfx/widgets/canvas/AbstractPainterRGB888.hpp>
#endif

using namespace touchgfx;

/**
 * @class PainterVerticalAlpha PainterVerticalAlpha.hpp gui/common/PainterVerticalAlpha.hpp
 *
 * @brief A Painter that will paint using a fading color.
 *
 *        PainterVerticalAlpha will paint using the given color at y coordinate 0 fading
 *        the color to invisible at the given y coordinate.
 *
 * @see AbstractPainter */
class PainterVerticalAlpha :
#if !defined(USE_BPP) || USE_BPP==16
    public AbstractPainterRGB565
#elif USE_BPP==24
    public AbstractPainterRGB888
#endif
{
public:

    /**
     * @fn PainterVerticalAlpha::PainterVerticalAlpha(colortype color = 0, int alpha0atY = 100);
     *
     * @brief Constructor.
     *
     *        Constructor.
     *
     * @param color     The color.
     * @param alpha0atY The y coordinate where alpha has faded to 0.
     */
    PainterVerticalAlpha(colortype color = 0, int alpha0atY = 100);

    /**
     * @fn void PainterVerticalAlpha::setColor(colortype color, int alphaZeroAt);
     *
     * @brief Sets color and alpha to use when drawing the CanvasWidget.
     *
     *        Sets color and alpha to use when drawing the CanvasWidget.
     *
     * @param color       The color.
     * @param alphaZeroAt The y coordinate where alpha has faded to 0.
     */
    void setColor(colortype color, int alphaZeroAt);

protected:
    /**
     * @fn virtual bool PainterVerticalAlpha::renderInit();
     *
     * @brief Get ready to render (part of) a scanline.
     *
     *        Get ready to render (part of) a scanline. Since the scanline will have the same y
     *        coordinate, the alpha for the scanline can be calculated here and used for all
     *        pixels in the scanline.
     *
     * @return true if it succeeds, false if it fails.
     */
    virtual bool renderInit();

    /**
     * @fn virtual bool PainterVerticalAlpha::renderNext(uint8_t &pixelRed, uint8_t &pixelGreen, uint8_t &pixelBlue, uint8_t &pixelAlpha);
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
    uint8_t alpha; ///< Current alpha for the scan line
    int alpha0atY; ///< The Y coordinate where alpha has faded to 0

private:
    /**
     * @fn virtual void renderPixel(uint16_t* p, uint8_t pixelRed, uint8_t pixelGreen, uint8_t pixelBlue);
     *
     * @brief Renders the pixel.
     *
     *        Renders the pixel, applying random noise to avoid banding.
     *
     * @param [in] p     Pointer to the frame buffer where the pixel should be put.
     * @param pixelRed   The red.
     * @param pixelGreen The green.
     * @param pixelBlue  The blue.
     */
    virtual void renderPixel(uint16_t *p, uint8_t pixelRed, uint8_t pixelGreen, uint8_t pixelBlue);
};

#endif /* PAINTERVERTICALALPHA_HPP */
