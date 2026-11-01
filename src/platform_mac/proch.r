#include "Processes.r"
resource 'SIZE' (-1) {
    reserved, ignoreSuspendResumeEvents, reserved, cannotBackground,
    needsActivateOnFGSwitch, backgroundAndForeground,
    dontGetFrontClicks, ignoreChildDiedEvents, is32BitCompatible,
    notHighLevelEventAware, onlyLocalHLEvents, notStationeryAware,
    dontUseTextEditServices, reserved, reserved, reserved,
    2048 * 1024, 1536 * 1024
};
