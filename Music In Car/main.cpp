#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

typedef struct song
{
  int time;
  int pleasure;
  int halftime;
} Song;

void get_halftime(Song* song)
{
  song->halftime = song->time / 2;
  if(song->time % 2 != 0)
  {
    song->halftime++;
  }
}

int get_playlist_time(Song* playlist, int x, int r, int w)
{
   int total = 0;
    std::vector<int> saves;

    for (int i = x; i <= r; i++)
    {
        total += playlist[i].time;
        saves.push_back(playlist[i].time - playlist[i].halftime); // 节省量
    }

    std::sort(saves.begin(), saves.end(), std::greater<int>());

    int take = std::min(w, (int)saves.size());
    for (int i = 0; i < take; i++)
    {
        total -= saves[i];
    }

    return total;
}

void get_max_pleasure(Song* playlist, int n, int w, int k)
{
  long long max_pleasure = 0;

for (int x = 0; x < n; x++)
{
    int best_r = -1;

    for (int r = x; r < n; r++)
    {
        if (get_playlist_time(playlist, x, r, w) <= k)
            best_r = r;
        else
            break;
    }

    if (best_r >= 0)
    {
        long long pleasure = 0;
        for (int i = x; i <= best_r; i++)
            pleasure += playlist[i].pleasure;

        if (pleasure > max_pleasure)
            max_pleasure = pleasure;
    }
}

std::cout << max_pleasure << std::endl;
}

int main()
{
  int n, w, k; //n:歌曲数量，w：可以听一部分的歌曲数量，k:可以听的歌曲总时间
  std::cin >> n >> w >> k;
  Song playlist[n];
  for(int i = 0; i < n; i++)
  {
    std::cin >> playlist[i].pleasure;
  }
  for(int i = 0; i < n; i++)
  {
    std::cin >> playlist[i].time;
    get_halftime(&playlist[i]);
  }

  //std::cout << "input cplt" << std::endl;

  get_max_pleasure(playlist, n, w, k);
  return 0;
}