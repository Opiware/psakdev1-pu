/* Copyright Statement:
 *
 */

#include <stdbool.h>
#include <stdint.h>
#include "bl_mtk_bb_reg.h"
#include "bl_common.h"
#include "bl_fota.h"

typedef enum {
    INIT_PHASE = 0,
    READ_PHASE,
    VERIFY_PHASE,
    UPDATE_PHASE,
    FINISH_PHASE
} bl_fota_progress_phase_t;


bool bl_fota_triggered()
{
    uint32_t fota_triggered = *BL_RETN_FLAG;
    if (fota_triggered & BL_RETN_FOTA_FULL_DL_EN) {
        return true;
    } else {
        return false;
    }
}

int bl_fota_update_progress(bl_fota_progress_phase_t phase, uint32_t progress)
{
    bl_print(LOG_DEBUG, " phase = %d , progress %d \r\n", phase, progress);
    return 0;
}

void bl_fota_process(void)
{
    if ( bl_fota_triggered() ) {
        /* start */
        bl_print(LOG_DEBUG, " start fota process \r\n");
        bl_fota_update_progress(INIT_PHASE, 0);

        /* TODO add customize fota process */

        /* after fota finish clear flag */
        bl_clear_retn_flag(BL_RETN_FOTA_FULL_DL_EN);

        /* finish */
        bl_print(LOG_DEBUG, " finish fota process \r\n");
        bl_fota_update_progress(FINISH_PHASE, 100);
    }
}
