#include <wx/wx.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/tokenzr.h>
#include <vector>
#include <sstream>

class PlagiarismCheckerFrame : public wxFrame {
public:
	PlagiarismCheckerFrame()
		: wxFrame(nullptr, wxID_ANY, "Plagiarism Checker") {
		wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

		inputTextCtrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
		referenceTextCtrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
		wxButton* checkButton = new wxButton(this, wxID_ANY, "Check Plagiarism");
		resultTextCtrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY);

		mainSizer->Add(inputTextCtrl, 1, wxEXPAND | wxALL, 10);
		mainSizer->Add(referenceTextCtrl, 1, wxEXPAND | wxALL, 10);
		mainSizer->Add(checkButton, 0, wxALIGN_CENTER | wxALL, 10);
		mainSizer->Add(resultTextCtrl, 1, wxEXPAND | wxALL, 10);

		SetSizerAndFit(mainSizer);

		Bind(wxEVT_BUTTON, &PlagiarismCheckerFrame::OnCheckPlagiarism, this, checkButton->GetId());
	}
	std::vector<wxString> GetMatchedWords(const wxString& inputText, const wxString& referenceText) {
		std::vector<wxString> inputWords = SplitTextIntoWords(inputText);
		std::vector<wxString> referenceWords = SplitTextIntoWords(referenceText);
		std::vector<wxString> matchedWords;

		for (const wxString& inputWord : inputWords) {
			for (const wxString& referenceWord : referenceWords) {
				if (inputWord.CmpNoCase(referenceWord) == 0) {
					matchedWords.push_back(inputWord);
					break;
				}
			}
		}

		return matchedWords;
	}

	void OnCheckPlagiarism(wxCommandEvent& event) {
		wxString inputText = inputTextCtrl->GetValue();
		wxString referenceText = referenceTextCtrl->GetValue();

		std::vector<wxString> matchedWords;
		double similarityScore = CalculateSimilarity(inputText, referenceText, matchedWords);

		wxString result;
		result << "Similarity Score: " << similarityScore << "%\n";

		if (similarityScore >= 50.0) {
			result << "Plagiarism detected!\n";
			result << "Plagiarized Words:\n";
			for (const wxString& word : matchedWords) {
				result << "- " << word << "\n";
			}
		}
		else {
			result << "No plagiarism detected.";
		}

		resultTextCtrl->SetValue(result);
	}

	double CalculateSimilarity(const wxString& inputText, const wxString& referenceText, std::vector<wxString>& matchedWords) {
		std::vector<wxString> inputWords = SplitTextIntoWords(inputText);
		std::vector<wxString> referenceWords = SplitTextIntoWords(referenceText);

		int totalWords = inputWords.size();
		int matchedWordCount = 0;

		for (const wxString& inputWord : inputWords) {
			for (const wxString& referenceWord : referenceWords) {
				if (inputWord.CmpNoCase(referenceWord) == 0) {
					matchedWordCount++;
					matchedWords.push_back(inputWord);
					break;
				}
			}
		}

		return (static_cast<double>(matchedWordCount) / totalWords) * 100.0;
	}


	std::vector<wxString> SplitTextIntoWords(const wxString& text) {
		std::vector<wxString> words;
		wxStringTokenizer tokenizer(text, " \t\r\n.,;?!");

		while (tokenizer.HasMoreTokens()) {
			wxString word = tokenizer.GetNextToken();
			words.push_back(word);
		}

		return words;
	}

	void OnUpdateResultText(wxCommandEvent& event) {
		UpdateResultEvent* updateResultEvent = dynamic_cast<UpdateResultEvent*>(event.GetEventObject());
		if (updateResultEvent) {
			double similarityScore = updateResultEvent->similarityScore;
			std::vector<wxString> matchedWords = updateResultEvent->matchedWords;

			std::stringstream result;
			result << "Similarity Score: " << similarityScore << "%\n";
			result << "Matched Words:\n";

			for (const wxString& word : matchedWords) {
				result << "- " << word << "\n";
			}

			resultTextCtrl->SetValue(result.str());
		}
	}

private:
	wxTextCtrl* inputTextCtrl;
	wxTextCtrl* referenceTextCtrl;
	wxTextCtrl* resultTextCtrl;

	class UpdateResultEvent : public wxCommandEvent {
	public:
		UpdateResultEvent(wxEventType eventType, int id)
			: wxCommandEvent(eventType, id) {}

		UpdateResultEvent(const UpdateResultEvent& other)
			: wxCommandEvent(other) {
			this->matchedWords = other.matchedWords;
			this->similarityScore = other.similarityScore;
		}

		wxEvent* Clone() const override {
			return new UpdateResultEvent(*this);
		}

		std::vector<wxString> matchedWords;
		double similarityScore;
	};

	wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(PlagiarismCheckerFrame, wxFrame)
EVT_COMMAND(wxID_ANY, wxEVT_COMMAND_TEXT_UPDATED, PlagiarismCheckerFrame::OnUpdateResultText)
wxEND_EVENT_TABLE()

class PlagiarismCheckerApp : public wxApp {
public:
	bool OnInit() override {
		wxInitAllImageHandlers();
		PlagiarismCheckerFrame* frame = new PlagiarismCheckerFrame();
		frame->Show();
		return true;
	}
};

wxIMPLEMENT_APP(PlagiarismCheckerApp);

