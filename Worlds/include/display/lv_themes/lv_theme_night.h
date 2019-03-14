/**
 * @file lv_theme_night.h
 *
 */


extern "C"


/*********************
 *      INCLUDES
 *********************/

#include "display/lv_conf.h"
#include "display/lv_themes/lv_theme.h"


/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Initialize the night theme
 * @param hue [0..360] hue value from HSV color space to define the theme's base color
 * @param font pointer to a font (NULL to use the default)
 * @return pointer to the initialized theme
 */
lv_theme_t * lv_theme_night_init(uint16_t hue, lv_font_t *font);

/**
 * Get a pointer to the theme
 * @return pointer to the theme
 */
lv_theme_t * lv_theme_get_night(void);

/**********************
 *      MACROS
 **********************/


 /* extern "C" */
