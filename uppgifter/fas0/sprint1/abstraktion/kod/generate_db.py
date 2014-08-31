import random
import sys

vowels = 'aeiouy'
consonants = 'bcdfghjklmnprqtsvxzw'
digits = '0123456789'

def randomChar(chars):
    return ''.join(random.choice(chars))

randomConsonant = lambda: randomChar(consonants)
randomVowel     = lambda: randomChar(vowels)
randomDigit     = lambda: randomChar(digits)

def randomNumber(size):
    return ''.join(randomDigit() for x in range(size))

def randomPhoneNumber():
    return randomNumber(3) + '-' + randomNumber(5)

def randomSyllable():
    return randomConsonant() + (randomVowel())

def randomName(syllables):
    return ''.join(randomSyllable() for x in range(syllables)).capitalize()

def main():
    if (sys.argv < 2):
        print "Usage: python generate_db.py [SIZE]"
    else:
        try:
            size = int(sys.argv[1])
            for i in range(size-1):
                print randomName(3), randomName(4)
                print randomPhoneNumber()
            print randomName(3), randomName(4)
            sys.stdout.write(randomPhoneNumber())
        except ValueError:
            "Could not parse argument as a number"

if __name__ == "__main__":
    main()
