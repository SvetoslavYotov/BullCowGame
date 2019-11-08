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
		ProcessGuess(Input);
	}
}

void UBullCowCartridge::InitialiseGame()
{
	PrintLine(TEXT("Welcome to Bulls and Cows!"));

	HiddenWord = TEXT("planet");
	Lives = (HiddenWord.Len() - 1) * 2;
	bGameOver = false;
	
	PrintLine(TEXT("Can you guess the %i letter word?\nYou have %i lives."), HiddenWord.Len(), Lives);
	PrintLine(TEXT("Type in your guess \nand press enter to continue."));
}

void UBullCowCartridge::EndGame()
{
	bGameOver = true;
	PrintLine(TEXT("Press enter to play again."));
}

void UBullCowCartridge::ProcessGuess(FString Guess)
{
	if (Guess == HiddenWord)
	{
		PrintLine(TEXT("\nCongratulations, you have won the game!"));
		EndGame();
		return;
	}
	else
	{
		--Lives;
		
		if (Lives > 0)
		{
			if (Guess.Len() != HiddenWord.Len())
			{
				PrintLine(TEXT("Wrong length.\nThe hidden word is %i letters long."), HiddenWord.Len());
				PrintLine(TEXT("You have %i lives remaining"), Lives);
				return;
			}
			if (!IsIsogram(Guess))
			{
				PrintLine(TEXT("No repeating letters!\nYour guess must be an isogram!"));
				PrintLine(TEXT("You have %i lives remaining"), Lives);
				return;
			}
		}
		else
		{
			PrintLine(TEXT("\nYou have lost!"));
			PrintLine(TEXT("The hidden word was: %s\n"), *HiddenWord);
			EndGame();
		}
	}
	
}

bool UBullCowCartridge::IsIsogram(FString Guess) const
{
	return true;
}
