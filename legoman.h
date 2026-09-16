#ifndef LEGOMAN_H
#define LEGOMAN_H


void head(void);
void torso(void);
void loadLegoTexture(void);
void headNoTexture(void);
void configureLighting(void);
void ingot(void);;
void meltingIngot(float time);
extern const float HEAD_HEIGHT;
const float INGOT_HEIGHT = 10;

#endif