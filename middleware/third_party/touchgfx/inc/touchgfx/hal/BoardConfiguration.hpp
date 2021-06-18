/* Copyright Statement:
 *
 */

#ifndef BOARDCONFIGURATION_HPP
#define BOARDCONFIGURATION_HPP

namespace touchgfx
{

/**
 * @fn void hw_init();
 *
 * @brief Function to perform generic hardware initialization of the board.
 *
 *        Function to perform generic hardware initialization of the board. This function
 *        prototype is only provided as a convention. */
void hw_init();

/**
 * @fn void touchgfx_init();
 *
 * @brief Function to perform touchgfx initialization.
 *
 *        Function to perform touchgfx initialization. This function prototype is only provided
 *        as a convention. */
void touchgfx_init();

} // namespace touchgfx




#endif // BOARDCONFIGURATION_HPP
