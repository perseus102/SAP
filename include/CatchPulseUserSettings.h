#pragma once

// 0 = light mode, 1 = dark mode
DWORD getCurrentThemeCP(DWORD& dwTheme);
DWORD setCurrentThemeCP(DWORD dwTheme);

// 0 = windowed, 1 = fullscreen
DWORD getFullScreenCP(DWORD &isFullScreen);
DWORD setFullScreenCP(DWORD isFullScreen);