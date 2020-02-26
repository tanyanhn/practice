#! /usr/bin/env python3


def pet_shop(animal, alive=True):
    # Define a function with the alive variable set to a default of True.
    print("Hello?!")
    if animal == "parrot":
        if not alive:
            print("Refunds in Bolton!")
        else:
            print("What a lovely parrot!")


def name_of_function(parameter):
    # "def" is required to denote the declaration of a function
    parameter = parameter + 1
    return parameter


age = 10
newage = name_of_function(age)
# Create a variable age and pass it to our function.
print(newage)  # should return '11'

my_pet = "parrot"
pet_shop(my_pet)
# Hello?!
# What a lovely parrot!
pet_shop(my_pet, False)
# Hello>!
# Refunds in Bolton!
