/******************************************************************/
/* Violet Engine                                                  */
/* (C) Devon Artmeier 2022                                        */
/******************************************************************/

#include "Violet.hpp"

namespace Violet {

	/// <summary>
	/// Buttons
	/// </summary>
	bool Input::buttons[static_cast<int>(Button::Count)]{ { 0 } };

	/// <summary>
	/// Previous buttons
	/// </summary>
	bool Input::buttonsPrev[static_cast<int>(Button::Count)]{ { 0 } };

	/// <summary>
	/// Analog inputs
	/// </summary>
	float Input::analog[static_cast<int>(Analog::Count)]{ { 0 } };

	/// <summary>
	/// Previous analog inputs
	/// </summary>
	float Input::analogPrev[static_cast<int>(Analog::Count)]{ { 0 } };

	/// <summary>
	/// Set up new frame of input
	/// </summary>
	void Input::NewFrame() {
		for (int i = 0; i < static_cast<int>(Button::Count); ++i) {
			buttonsPrev[i] = buttons[i];
		}
		for (int i = 0; i < static_cast<int>(Analog::Count); ++i) {
			analogPrev[i] = analog[i];
		}
	}

	/// <summary>
	/// Check if a button is being pressed
	/// </summary>
	/// <param name="button">Button ID</param>
	/// <returns>True if pressed, false if not</returns>
	bool Input::CheckButtonPress(Button button) {
		int id = static_cast<int>(button);
		return buttons[id];
	}

	/// <summary>
	/// Check if a button was tapped
	/// </summary>
	/// <param name="button">Button ID</param>
	/// <returns>True if tapped, false if not</returns>
	bool Input::CheckButtonTap(Button button) {
		int id = static_cast<int>(button);
		return buttons[id] && !buttonsPrev[id];
	}

	/// <summary>
	/// Check if a button was released
	/// </summary>
	/// <param name="button">Button ID</param>
	/// <returns>True if released, false if not</returns>
	bool Input::CheckButtonRelease(Button button) {
		int id = static_cast<int>(button);
		return !buttons[id] && buttonsPrev[id];
	}

}
