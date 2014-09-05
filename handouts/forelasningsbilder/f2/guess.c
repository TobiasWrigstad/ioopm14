#include <stdlib.h>
#include <stdio.h>

int generate_random_number(int upper_bound)
{
  return random() % upper_bound;
}

void guess_loop(int answer, int guesses)
{
  while (guesses--)
    {
      int guess;
      scanf("%d", &guess);

      if (guess == answer)
	{
	  puts("Well done!");
	  break;
	}

      if (guess < answer)
	{
	  puts("Too low!");
	}
      else
	{
	  puts("Too high!");
	}
    }
}

int main(int argc, char *argv[])
{
  if (argc == 3)
    {
      int upper_bound = atoi(argv[1]);
      int guesses = atoi(argv[2]);

      int answer = generate_random_number(upper_bound);

      printf("Using at most %d guesses, guess a number in [0..%d]:\n", guesses, upper_bound);
      guess_loop(answer, guesses);
    }
  else
    {
      puts("Usage: ./guess upper-bound number-of-guesses");
    }

  return 0;
}
