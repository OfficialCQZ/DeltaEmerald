#ifndef GUARD_DELTA_SPRITES_INTERFACE_H
#define GUARD_DELTA_SPRITES_INTERFACE_H

struct DeltaOAMs
{
    const struct SpritePalette *palette;
    struct SpriteTemplate *template;
};

u8 AddDeltaEmeraldObject(u8, s16, s16, u8);

#endif // GUARD_DELTA_SPRITES_INTERFACE_H
