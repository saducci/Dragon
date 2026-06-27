#include <raylib.h>
// #include <vector>
class Textures_txt {
public:
  Texture2D backgroundimage =
      LoadTexture("resource/Background/parallax-mountain-bg.png");
  Texture2D dragon = LoadTexture("resource/spr_monster_right2.png");
  Texture2D dirt_block = LoadTexture("resource/dirt_fixed_2.png");
  Rectangle source_backgroundimage = {0, 0, float(backgroundimage.width),
                                      float(backgroundimage.height)};

  Rectangle dest_backgroundimage = {0, 0, GetScreenWidth() * 5.0f, 1000};

  float groundY = GetScreenHeight() - dirt_block.height - dragon.height;

  float x_drag = 0;
  float y_drag = GetScreenHeight() - dirt_block.height - dragon.height;
  float y_drag_dest = y_drag + dragon.height * (1 - 2.0f) + 10;
  void Drawbackground() {
    for (int y = groundY + dragon.height; y < 1500; y += dirt_block.height)
      for (int x = 0; x < GetScreenWidth() * 5; x += dirt_block.width) {
        DrawTexture(dirt_block, x, y, WHITE);
      }
  }
  void Drawdragon(bool facing_right) {

    float scale = 2.0f;

    Rectangle source = {0, 0, (float)dragon.width, (float)dragon.height};

    if (!facing_right) {
      source.width = -dragon.width;
    }

    Rectangle dest = {x_drag, y_drag + (dragon.height * (1 - scale)) + 10,
                      dragon.width * scale, dragon.height * scale};

    DrawTexturePro(dragon, source, dest, {0, 0}, 0, WHITE);
  }
  void Drawbackgroundimage() {
    DrawTexturePro(backgroundimage, source_backgroundimage,
                   dest_backgroundimage, {0, 0}, 0, RAYWHITE);
  }
};
class Dragon_movment {
public:
  float velocityX = 0.0f;
  float velocityY = 0.0f;
  const float gravity = 0.5f;
  bool dragon_floor = true;
  bool facing_right = true;

  void dragon_movment(Textures_txt &text) {
    if (IsKeyPressed(KEY_W) && dragon_floor) {
      velocityY = -20.0f;
      dragon_floor = false;
    }
    if (!dragon_floor) {
      velocityY += gravity;
      text.y_drag += velocityY;
    }
    if (text.y_drag >= text.groundY) {
      text.y_drag = text.groundY;
      velocityY = 0.0f;
      dragon_floor = true;
    }
    if (IsKeyDown(KEY_D)) {
      velocityX = 10;

      if (text.x_drag + text.dragon.width * 2 < GetScreenWidth() * 5.0f) {
        text.x_drag += velocityX;
      }

      facing_right = true;
    }
    else if (IsKeyDown(KEY_A)) {
      velocityX = -10;

      if (text.x_drag > 0) {
        text.x_drag += velocityX;
      }

      facing_right = false;
    }
  }
};
int main() {
  const int width = 1920;
  const int height = 1080;

  InitWindow(width, height, "SaCraft");
  SetTargetFPS(60);
  Textures_txt texture_user;
  Dragon_movment player;
  // bullet bullet;
  Camera2D camera = {0};
  camera.offset = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;

  while (!WindowShouldClose()) {

    player.dragon_movment(texture_user);
    float worldWidth = GetScreenWidth() * 5.0f;
    float worldHeight = GetScreenHeight() * 5.0f;

    Vector2 target = {texture_user.x_drag + texture_user.dragon.width / 2.0f,
                      texture_user.y_drag + texture_user.dragon.height / 2.0f -80};

    // screen center
    float screenW = GetScreenWidth();
    float screenH = GetScreenHeight();

    // clamp X
    if (target.x < screenW / (2 * camera.zoom)) {
      target.x = screenW / (2 * camera.zoom);
    }
    if (target.x > worldWidth - screenW / (2 * camera.zoom)) {
      target.x = worldWidth - screenW / (2 * camera.zoom);
    }
    // clamp Y
    if (target.y < screenH / (2 * camera.zoom)) {
      target.y = screenH / (2 * camera.zoom);
    }

    if (target.y > worldHeight - screenH / (2 * camera.zoom)) {

      target.y = worldHeight - screenH / (2 * camera.zoom);
    }

    camera.target = target;

    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode2D(camera);
    texture_user.Drawbackgroundimage();
    texture_user.Drawbackground();
    texture_user.Drawdragon(player.facing_right);
    //  bullet.shoot(texture_user, player);
    EndMode2D();
    EndDrawing();
  }

  UnloadTexture(texture_user.dirt_block);
  UnloadTexture(texture_user.dragon);
  UnloadTexture(texture_user.backgroundimage);

  CloseWindow();
}
