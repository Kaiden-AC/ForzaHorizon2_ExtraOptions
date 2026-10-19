#include "no_damage.h"
#include "game_addresses.h"

// The local car exposes its damage through a deferred presentation wrapper, so
// the game's own "reset visible damage" routine is replayed on the player car
// every frame from the existing local-car update hook. That routine clears the
// dent grid, the glass damage and reattaches detached body panels through the
// deferred command queue, matching the game's ResetCarDamage state when it
// leaves simulated damage alone. Mechanical damage, saved damage state and
// every other car are untouched.

typedef void (*CarGraphicsReset)(void *);

static unsigned char *game_image;
static int enabled;

void no_damage_bind(unsigned char *image) {
    game_image = image;
}

void no_damage_set_enabled(int value) {
    enabled = value != 0;
}

void no_damage_tick(void *car) {
    if (!enabled || !game_image || !car) {
        return;
    }
    ((CarGraphicsReset)(game_image + GAME_RVA_CAR_RESET_GRAPHICS_DAMAGE))(car);
    ((CarGraphicsReset)(game_image + GAME_RVA_CAR_RESET_HELPER))(car);
}
