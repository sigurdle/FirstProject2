void Draw3DRect(HDC hDC, int x, int y, int cx, int cy, COLORREF light, COLORREF dark);
void Draw3DRect(HDC hDC, int x, int y, int cx, int cy, RGBQUAD light, RGBQUAD dark);
void Draw3DRect(HDC hDC, RECT* rect, COLORREF light, COLORREF dark);
void FillSolidRect(HDC hDC, RECT* rect, COLORREF clr);
void FillSolidRect(HDC hDC, int left, int top, int width, int height, COLORREF clr);
void DrawVertGradient(HDC hDC, RECT* rect, COLORREF light, COLORREF dark);
void DrawHorzGradient(HDC hDC, RECT* rect, COLORREF light, COLORREF dark);
void DrawVertGradient(HDC hDC, RECT& rect, COLORREF light, COLORREF dark);
void DrawHorzGradient(HDC hDC, RECT& rect, COLORREF light, COLORREF dark);

void TransparentBlt(HDC pDestDc, int x, int y, int w, int h, HBITMAP pBmp, int sx, int sy, COLORREF crTransparent);

#define ROWBYTES(width,bitcount)			((((width)*(bitcount)+31) >> 3) & 0xfffc)
