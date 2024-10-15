// test_math_game.cpp

#include <gtest/gtest.h>
#include "pet_stats.h"
#include "MATHGAME.h"  // Include the header file for the math game

// Test initializing the math game
TEST(MathGameTest, Initialization) {
    MathGame game;  // Create an instance of the MathGame class
    EXPECT_EQ(game.getScore(), 0);  // Check that the initial score is 0
    EXPECT_EQ(game.getCurrentLevel(), 1);  // Check that the initial level is 1
}

// Test correct answer functionality
TEST(MathGameTest, CorrectAnswer) {
    MathGame game;
    game.generateQuestion();  // Generate a new question
    int correctAnswer = game.getCurrentAnswer();  // Get the correct answer

    EXPECT_TRUE(game.submitAnswer(correctAnswer));  // Submit the correct answer
    EXPECT_GT(game.getScore(), 0);  // Ensure the score increases
}

// Test incorrect answer functionality
TEST(MathGameTest, IncorrectAnswer) {
    MathGame game;
    game.generateQuestion();  // Generate a new question
    int incorrectAnswer = game.getCurrentAnswer() + 1;  // Get a wrong answer

    EXPECT_FALSE(game.submitAnswer(incorrectAnswer));  // Submit an incorrect answer
    EXPECT_EQ(game.getScore(), 0);  // Ensure the score remains the same
}

// Test level progression functionality
TEST(MathGameTest, LevelProgression) {
    MathGame game;
    
    for (int i = 0; i < 5; ++i) {
        game.generateQuestion();
        int correctAnswer = game.getCurrentAnswer();
        game.submitAnswer(correctAnswer);  // Assume the answer is always correct
    }
    
    EXPECT_EQ(game.getCurrentLevel(), 2);  // Check if the level increased after answering 5 questions
}

// Test earning money based on performance
TEST(MathGameTest, EarnMoneyBasedOnScore) {
    MathGame game;
    game.generateQuestion();
    int correctAnswer = game.getCurrentAnswer();

    game.submitAnswer(correctAnswer);  // Assume a correct answer

    int earnedMoney = game.calculateEarnings();  // Calculate earnings based on score
    EXPECT_GT(earnedMoney, 0);  // Ensure money is earned based on correct answers
}

