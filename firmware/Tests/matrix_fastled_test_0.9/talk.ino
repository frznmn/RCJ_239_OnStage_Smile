void talk()
{
  if (millis() % 1000 > 500)
  {
    matrix->drawRGBBitmap(0, 0, (const uint16_t *) default_bitmap, 16, 8);
    matrix->show();
  }
  else
  {
    matrix->drawRGBBitmap(0, 0, (const uint16_t *) dvizh, 16, 8);
    matrix->show();
  }
}
