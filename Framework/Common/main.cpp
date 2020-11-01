#include "../Interface/IApplication.hpp"
#include <stdio.h>

using namespace My;

namespace My {
extern IApplication *g_App;
}

int main(int argc, char *argv[]) {
  printf("Hello World!\n");

  int ret = 0;

  if ((ret = g_App->Initialize()) != 0) {
    printf("App Initialize failed, will exit now!");
    return ret;
  }

  while (!g_App->IsQuit()) {
    g_App->Tick();
  }

  g_App->Finalize();
  return 0;
}
