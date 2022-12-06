/******************************************************************/
/* Violet Engine                                                  */
/* (C) Devon Artmeier 2022                                        */
/******************************************************************/

#ifndef VIOLET_INPUT_HPP
#define VIOLET_INPUT_HPP

namespace Violet {

	/// <summary>
	/// Input buttons
	/// </summary>
	enum class Button {
		/// <summary>
		/// A button
		/// </summary>
		A = 0,
		
		/// <summary>
		/// B button
		/// </summary>
		B,

		/// <summary>
		/// X button
		/// </summary>
		X,

		/// <summary>
		/// Y button
		/// </summary>
		Y,

		/// <summary>
		/// Left
		/// </summary>
		Left,

		/// <summary>
		/// Right
		/// </summary>
		Right,

		/// <summary>
		/// Up
		/// </summary>
		Up,
		
		/// <summary>
		/// Down
		/// </summary>
		Down,

		/// <summary>
		/// Left bumper
		/// </summary>
		LeftBumper,

		/// <summary>
		/// Left stick
		/// </summary>
		LeftStick,

		/// <summary>
		/// Right bumper
		/// </summary>
		RightBumper,

		/// <summary>
		/// Right stick
		/// </summary>
		RightStick,

		/// <summary>
		/// Button type count
		/// </summary>
		Count
	};

	/// <summary>
	/// Analog inputs
	/// </summary>
	enum Analog {
		/// <summary>
		/// Left stick
		/// </summary>
		LeftStick = 0,

		/// <summary>
		/// Right stick
		/// </summary>
		RightStick,

		/// <summary>
		/// Left trigger
		/// </summary>
		LeftTrigger,

		/// <summary>
		/// Right trigger
		/// </summary>
		RightTrigger,

		/// <summary>
		/// Analog input type count
		/// </summary>
		Count
	};

	/// <summary>
	/// Input
	/// </summary>
	class Input {
	public:
		/// <summary>
		/// Check if a button is being pressed
		/// </summary>
		/// <param name="button">Button ID</param>
		/// <returns>True if pressed, false if not</returns>
		static bool CheckButtonPress(Button button);

		/// <summary>
		/// Check if a button was tapped
		/// </summary>
		/// <param name="button">Button ID</param>
		/// <returns>True if tapped, false if not</returns>
		static bool CheckButtonTap(Button button);

		/// <summary>
		/// Check if a button was released
		/// </summary>
		/// <param name="button">Button ID</param>
		/// <returns>True if released, false if not</returns>
		static bool CheckButtonRelease(Button button);

		// Friend classes
		friend class Engine;
		friend class Shell;

	private:
		/// <summary>
		/// Set up new frame of input
		/// </summary>
		static void NewFrame();

		/// <summary>
		/// Buttons
		/// </summary>
		static bool buttons[static_cast<int>(Button::Count)];

		/// <summary>
		/// Previous buttons
		/// </summary>
		static bool buttonsPrev[static_cast<int>(Button::Count)];

		/// <summary>
		/// Analog inputs
		/// </summary>
		static float analog[static_cast<int>(Analog::Count)];

		/// <summary>
		/// Previous analog inputs
		/// </summary>
		static float analogPrev[static_cast<int>(Analog::Count)];
	};

}

#endif // VIOLET_INPUT_HPP
