Christopher Zhu
UID:104455996

This lab was relatively interesting and mildly confusing to perform at 
times. In this lab, I modified the ray tracer give it multi-threaded 
capabilities in order to improve performance of the program. 

I ran into a couple issues while modifying the file. A big issue was the 
that I was getting issues after using global variables. After spending a 
couple hours trying to figure out what was wrong, I realized that I had 
local variables with the same names in functions which would then cause me 
problems because the global variable wouldn't be modified after modifying 
the variable within the function. 

Another issue I ran into was that my logic resulted in a picture that was 
facing southwards so it was 90 degrees off. I thought my logic was right 
which made me relatively frustrated. After playing around with my code, I 
was able to obtain the correct image by flipping the px and py values when I 
made calculations to determine the index for my global array. I 
misinterpreted the program in thinking that it printed from left to right 
and then up to down when it prints up to down then left to right. 

Afterwards, another issue I ran into was that I had was handling the new 
lines for the output. I was able to solve these problems by creating special 
cases to handle the first and last iteration of new lines. I do this by 
checking to make sure my index is not 0 when I factor in putting in new 
lines. Next to handle the last new line problem because I was missing a new 
line at the end, I just manually inputted a new line. This solved my problem 
and resulted in a diff output of nothing. 

Next, the last issue I had was when I started using multiple threads 
since to test the program I only used one thread. I was able to fix this 
since the main problem was my algorithm was incorrect for handling multiple 
threads even though I thought it was correct. This arithmetic problem didn't 
take that long to fix which was nice. 

Finally, the last problem I had was that the picture would be mostly printed 
but be black bars in some places. I quickly realized this was an error with 
my implementation of the remainder when the number of threads doesn't divide 
equally. I fixed this through more arithmetic logic thinking and was able to 
finally produce the correct image after checking with diff -u command. 




My output after make clean is shown below which shows the time: 
[christoz@lnxsrv01 ~/Desktop/srt]$ make clean check
rm -f *.o *.tmp 1-test.ppm 2-test.ppm 4-test.ppm 8-test.ppm srt srt.tgz
gcc -std=gnu99 -g -O2 -Wall -Wextra -Wno-unused-parameter   -c -o main.o 
main.c
gcc -std=gnu99 -g -O2 -Wall -Wextra -Wno-unused-parameter   -c -o raymath.o 
raymath.c
gcc -std=gnu99 -g -O2 -Wall -Wextra -Wno-unused-parameter   -c -o shaders.o 
shaders.c
gcc -std=gnu99 -g -O2 -Wall -Wextra -Wno-unused-parameter -o srt main.o 
raymath.o shaders.o -lm -lpthread
time ./srt 1-test.ppm >1-test.ppm.tmp

real    0m48.062s
user    0m48.067s
sys     0m0.000s
mv 1-test.ppm.tmp 1-test.ppm
time ./srt 2-test.ppm >2-test.ppm.tmp

real    0m25.027s
user    0m48.525s
sys     0m0.000s
mv 2-test.ppm.tmp 2-test.ppm
time ./srt 4-test.ppm >4-test.ppm.tmp

real    0m16.439s
user    0m48.327s
sys     0m0.002s
mv 4-test.ppm.tmp 4-test.ppm
time ./srt 8-test.ppm >8-test.ppm.tmp

real    0m10.573s
user    0m50.096s
sys     0m0.007s
mv 8-test.ppm.tmp 8-test.ppm
for file in 1-test.ppm 2-test.ppm 4-test.ppm 8-test.ppm; do \
  diff -u baseline.ppm $file || exit; \
done


These results show that my implementation is pretty good since it cuts down 
the time when there are more threads. As we can see from the results, the 
difference between using 8 threads and 1 threads is a speedup of a factor of 
5 which is really good for performance.