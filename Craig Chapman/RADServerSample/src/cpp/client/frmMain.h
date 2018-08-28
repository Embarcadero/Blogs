//---------------------------------------------------------------------------

#ifndef frmMainH
#define frmMainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <Data.Bind.Components.hpp>
#include <Data.Bind.ObjectScope.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.DateTimeCtrls.hpp>
#include <FMX.Edit.hpp>
#include <FMX.EditBox.hpp>
#include <FMX.SpinBox.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <IPPeerClient.hpp>
#include <REST.Client.hpp>
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel3;
	TLabel *lblFirstName;
	TLabel *lblLastName;
	TLabel *lblEmployeeNumber;
	TLabel *lblPhoneExt;
	TLabel *lblHireDate;
	TLabel *lblDepartmentNumber;
	TLabel *lblJobCode;
	TLabel *lblJobGrade;
	TLabel *lblJobCountry;
	TLabel *lblSalary;
	TEdit *edFirstName;
	TEdit *edLastName;
	TEdit *edtPhoneExt;
	TEdit *edtJobCode;
	TEdit *edtJobGrade;
	TEdit *edtJobCountry;
	TSpinBox *spedEmployeeNumber;
	TSpinBox *spedDepartmentNumber;
	TDateEdit *dtedHireDate;
	TPanel *Panel1;
	TButton *btnPrev;
	TButton *btnNext;
	TButton *btnRead;
	TButton *btnCreate;
	TButton *btnCommit;
	TButton *btnEdit;
	TButton *btnUpdate;
	TButton *btnDelete;
	TButton *btnFirst;
	TButton *btnLast;
	TSpinBox *spedSalary;
	TPanel *Panel2;
	TRESTClient *RESTClient;
	TRESTRequest *RESTRequest;
	TRESTResponse *RESTResponse;
	void __fastcall btnReadClick(TObject *Sender);
	void __fastcall btnPrevClick(TObject *Sender);
	void __fastcall btnNextClick(TObject *Sender);
	void __fastcall btnFirstClick(TObject *Sender);
	void __fastcall btnLastClick(TObject *Sender);
	void __fastcall btnCreateClick(TObject *Sender);
	void __fastcall btnCommitClick(TObject *Sender);
	void __fastcall btnEditClick(TObject *Sender);
	void __fastcall btnUpdateClick(TObject *Sender);
	void __fastcall btnDeleteClick(TObject *Sender);
private:	// User declarations
	TJSONArray* fJSONArray;
	int fCurrentIndex;
private:
	void JSONToForm();
	void ClearForm();
	void CreateMode();
	void BrowseMode();
	void EditMode();
public:		// User declarations
	__fastcall TForm2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
