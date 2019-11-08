// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
	
	InitialiseGame(); // Setting up the game
	
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
	if (bGameOver)
	{
		ClearScreen();
		InitialiseGame();
	}
	else
	{
		if (Input == HiddenWord)
		{
			PrintLine(TEXT("Congratulations, you have won the game!"));
			EndGame();
		}
		else
		{
			if (Input.Len() != HiddenWord.Len())
			{
				PrintLine(TEXT("The word is %i characters long. \nYou have lost!"), HiddenWord.Len());
				EndGame();
			}
		}
	}
}

void UBullCowCartridge::InitialiseGame()
{
	PrintLine(TEXT("Welcome to Bulls and Cows!\nA fun word game!"));

	HiddenWord = TEXT("planet");
	Lives = (HiddenWord.Len() - 1) * 2;
	bGameOver = false;
	
	PrintLine(TEXT("Can you guess the %i letter word?"), HiddenWord.Len());
	PrintLine(TEXT("Type in your guess. \nPress enter to continue."));
}

void UBullCowCartridge::EndGame()
{
	bGameOver = true;
	PrintLine(TEXT("Press enter to play again."));
}