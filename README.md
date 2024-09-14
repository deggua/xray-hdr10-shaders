# xray-hdr10-shaders

These are shaders that support HDR10 output from a modified version of the xray-monolith engine

* `GAMMA` - For G.A.M.M.A. (modified `common_functions.h` from Enhanced Shaders by KennShade, modified `combine_2_naa.ps` from SSS20 by Ascii1457 with Beef's NVGs compatibility fixes)

## Configuration
I don't think any vanilla effects (e.g. DOF, bloom, etc.) are incompatible, the ones that are should be disabled automatically when HDR10 output is enabled.

You don't need to disable `r2_tonemap`, that option is poorly named, it's actually auto-exposure, which you might want to use if a fixed exposure value doesn't work for you.

If you find an issue, create an issue on GitHub and I'll look into it. Please provide screenshots (preferably HDR ones, you can take them with the nVidia overlay with Alt+F1, they're JXR files which you'll need an HDR image viewer for if you want to view them correctly: [this one is free](https://apps.microsoft.com/detail/9pgn3nwpbwl9?hl=en-US&gl=US)) and a complete description of what the problem is.
