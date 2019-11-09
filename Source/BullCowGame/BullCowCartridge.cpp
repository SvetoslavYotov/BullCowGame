// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordsList.h"



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

	HiddenWord = HiddenWordsList[FMath::RandRange(0, HiddenWordsList.Num() - 1)];
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

void UBullCowCartridge::ProcessGuess(const FString& Guess)
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
			FBullCowCount Score = GetBullsCows(Guess);
			PrintLine(TEXT("You have %i Bulls and %i Cows"), Score.Bulls, Score.Cows);
			PrintLine(TEXT("You have %i lives remaining."), Lives);
		}
		else
		{
			PrintLine(TEXT("\nYou have lost!"));
			PrintLine(TEXT("The hidden word was: %s\n"), *HiddenWord);
			EndGame();
		}
	}
}

bool UBullCowCartridge::IsIsogram(const FString& Guess) const
{
	for (int32 Index = 0; Index < Guess.Len(); Index++)
	{
		for (int32 Comparison = Index + 1; Comparison < Guess.Len(); Comparison++)
		{
			if (Guess[Index] == Guess[Comparison])
			{
				return false;
			}
		}
	}
	return true;
}

FBullCowCount UBullCowCartridge::GetBullsCows(const FString& Guess) const
{
	FBullCowCount Count;
	for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
	{
		if (Guess[GuessIndex] == HiddenWord[GuessIndex])
		{
			Count.Bulls++;
			continue;
		}
		for (int32 HiddenIndex = 0; HiddenIndex < HiddenWord.Len(); HiddenIndex++)
		{
			if (Guess[GuessIndex] == HiddenWord[HiddenIndex])
			{
				Count.Cows++;
			}
		}
	}

	return Count;
}
