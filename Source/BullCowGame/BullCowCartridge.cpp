// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
	PrintLine(TEXT("Welcome to Bulls and Cows!\nA fun word game!"));
	PrintLine(TEXT("Guess the 6 letter word."));
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
	ClearScreen();
	FString HiddenWord = TEXT("planet");
	if (Input == HiddenWord)
	{
		PrintLine(TEXT("Congratulations, you have won the game!"));
	}
	else
	{
		PrintLine(TEXT("Wrong guess! Sorry, you lose."));
	}
	


}