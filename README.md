

The Plagiarism Checker is a C++ application developed using the wxWidgets library. It provides a graphical user interface (GUI) for comparing two pieces of text and determining the similarity between them. The application calculates a similarity score based on the matched words between the input text and a reference text, allowing users to detect potential plagiarism.

Key Features
Graphical user interface (GUI) for easy interaction.
Input fields for entering the input text and reference text.
Ability to calculate the similarity score between the input text and reference text.
Display of the similarity score as a percentage.
Detection of plagiarized words and listing them in the result display.
Asynchronous result updating for smoother user experience.
Usage
Launch the Plagiarism Checker application.
Enter the input text and reference text in the respective input fields.
Click the "Check Plagiarism" button to initiate the plagiarism check.
The application calculates the similarity score and displays the result, including the percentage score and any plagiarized words detected.
Requirements
C++ compiler with support for C++11 standard.
wxWidgets library installed.
Compatible operating system (Windows, macOS, Linux).
How to Build and Run
Ensure that you have a C++ compiler and the wxWidgets library installed on your system.
Clone or download the repository containing the source code for the Plagiarism Checker application.
Navigate to the directory containing the source code files.
Compile the source code using the appropriate compiler command, linking against the wxWidgets library.
css
Copy code
g++ -o PlagiarismChecker.exe main.cpp `wx-config --cxxflags --libs`
Run the compiled executable to launch the Plagiarism Checker application.
Credits
Developed by Muhammad Humais Aslam
