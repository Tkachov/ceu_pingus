# Versions comparison

## Resources usage

![C++ vs Céu](https://tkachov.ru/images/3IGnfzL492GCOxUvwLLZiulHsV_pkPooj5cO5yTG/comparsion.png)

CPU peaks correspond smooth transition between the screens where a lot of redrawings happen.

We can see that in C++ memory usage is rising during the **Level B** interval. At the same time, CPU is used in both fast-forward and usual modes equally. C++ version has no caching mechanism, so it requires more memory and I/O every time new Pingus is spawned (and, I guess, changes the action). I've added such mechanism in Céu version, so no additional loads required and less memory is consumed.

In Céu we can see that during the levels CPU is used more than in C++ version, and usage value slowly rises. There are two peaks, which correspond to fast-forward mode. During the **Level A** interval CPU usage is higher than in C++. Still, it's steady. I think that's because Pingus appear and exit the level almost simultaneously.

We can see it uses memory similarly to C++ version. It's around 93 MB in C++ at peak and around 85 MB in Céu at peak. At the same time, C++ frees unneeded resources and Céu doesn't - I've made some changes in surface loading, adding special cache storage. Because of that there are no duplicate sprites, but all loaded textures are kept in memory until the end. So, there is no overhead in Céu version, and that effect is completely because of cache I've added.

We found out that CPU usage rises with amount of Pingus in the level. So, it's a known issue we're going to examine more closely and fix eventually.

## FPS

I measured the maximum FPS in C++ and Céu versions of the game. Here are the results:

![C++ FPS](https://tkachov.ru/images/kbeciHjv8ZuCSGpVhqLHZylrzbw5Mu07WglEyU97/image6.png)
*C++ FPS without limiter*

In simple screens C++ reaches 10,000 FPS. Still, during the levels this value is in 3,500-4,000 interval.

![Céu FPS](https://tkachov.ru/images/llzc1osK6OPgLnCqihD4dPRZSB04G5q1rpfteXDl/image5.png)
*Céu FPS without limiter*

Céu has a little bit less impressive results. In simple screens FPS is around 5,000. During the levels FPS is somewhere between 300 and 1,000.

Considering level game play only, the numbers are `C++ = 3.5-4.0k` and `Céu = 0.3-1.0k`. C++ is 10 times faster in the worst case (0.3 vs 3.5).

Still, CPU usage issue in Céu affects FPS value as well. Fixing that we can assume that FPS won't fall during the game play (as C++ FPS is not falling during levels) and thus C++ is only 4 times faster. Again, we can't be sure that fixing that issue wouldn't rise FPS value to 2,000 or more. That would require additional measures later.