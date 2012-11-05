#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(MasterController *controllerParam, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    controller(controllerParam)
{
    ui->setupUi(this);

    //Disable UI elements for features not yet implemented
    ui->RunReportsPushButton->setEnabled(false);
    ui->CreateConsultationPushButton->setEnabled(false);

    //Initially, only the patient tab is displayed.
    ui->DisplayTabsWidget->setTabEnabled(1, false);
    ui->DisplayTabsWidget->setTabEnabled(2, false);

    //All of the elements of the patient tab are grayed out until one is
    //selected, or until a new one is to be created
    disablePatientEditing();

    //Populate list of physicians in consultation tab
    populatePhysicians();

    ui->statusbar->showMessage("Welcome to CuCare v0.0.1");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_NewPatientPushButton_clicked()
{
    enablePatientEditing();
}

void MainWindow::on_SelectPatientPushButton_clicked()
{
    PatientSelectDialog *patientWindow = new PatientSelectDialog(controller);

    if (patientWindow->exec() == 1) {
        enablePatientEditing();
        ui->CreateConsultationPushButton->setEnabled(true);

        //Populate patient info tab
        showPatientInfo();
    }
}

void MainWindow::enablePatientEditing()
{
    ui->FirstNameLineEdit->setEnabled(true);
    ui->LastNameLineEdit->setEnabled(true);

    ui->WorkPhoneLineEdit->setEnabled(true);
    ui->CellPhoneLineEdit->setEnabled(true);
    ui->EmailLineEdit->setEnabled(true);
    ui->WorkEmailLineEdit->setEnabled(true);

    ui->Address1LineEdit->setEnabled(true);
    ui->Address2LineEdit->setEnabled(true);
    ui->CityLineEdit->setEnabled(true);
    ui->CountryLineEdit->setEnabled(true);
    ui->PostalCodeLineEdit->setEnabled(true);

    ui->DOBDateEdit->setEnabled(true);
    ui->AddedDateEdit->setEnabled(true);
    ui->CardNumberLineEdit->setEnabled(true);
    ui->CardExpirationDateEdit->setEnabled(true);

    ui->DeletePatientPushButton->setEnabled(true);
    ui->PatientNotesTextEdit->setEnabled(true);
}

void MainWindow::disablePatientEditing()
{
    ui->FirstNameLineEdit->setEnabled(false);
    ui->LastNameLineEdit->setEnabled(false);

    ui->WorkPhoneLineEdit->setEnabled(false);
    ui->CellPhoneLineEdit->setEnabled(false);
    ui->EmailLineEdit->setEnabled(false);
    ui->WorkEmailLineEdit->setEnabled(false);

    ui->Address1LineEdit->setEnabled(false);
    ui->Address2LineEdit->setEnabled(false);
    ui->CityLineEdit->setEnabled(false);
    ui->CountryLineEdit->setEnabled(false);
    ui->PostalCodeLineEdit->setEnabled(false);

    ui->DOBDateEdit->setEnabled(false);
    ui->AddedDateEdit->setEnabled(false);
    ui->CardNumberLineEdit->setEnabled(false);
    ui->CardExpirationDateEdit->setEnabled(false);

    ui->DeletePatientPushButton->setEnabled(false);
    ui->PatientNotesTextEdit->setEnabled(false);
}

void MainWindow::showPatientInfo()
{
    //Switch to patient tab and disable other tabs
    ui->DisplayTabsWidget->setTabEnabled(0, true);
    ui->DisplayTabsWidget->setCurrentIndex(0);
    ui->DisplayTabsWidget->setTabEnabled(1, false);
    ui->DisplayTabsWidget->setTabEnabled(2, false);

    //Populate fields with patient info
    ui->FirstNameLineEdit->setText(QString::fromStdString(controller->getCurrentPatient()->getFirstName()));
    ui->LastNameLineEdit->setText(QString::fromStdString(controller->getCurrentPatient()->getLastName()));

    ui->WorkPhoneLineEdit->setText(QString::fromStdString(controller->getCurrentPatient()->getContact().getWorkPhone()));
    ui->CellPhoneLineEdit->setText(QString::fromStdString(controller->getCurrentPatient()->getContact().getCellPhone()));
    ui->EmailLineEdit->setText(QString::fromStdString(controller->getCurrentPatient()->getContact().getEmail()));
    ui->WorkEmailLineEdit->setText(QString::fromStdString(controller->getCurrentPatient()->getContact().getWorkEmail()));

    ui->Address1LineEdit->setText(QString::fromStdString(controller->getCurrentPatient()->getAddress().getLineOne()));
    ui->Address2LineEdit->setText(QString::fromStdString(controller->getCurrentPatient()->getAddress().getLineTwo()));
    ui->CityLineEdit->setText(QString::fromStdString(controller->getCurrentPatient()->getAddress().getCity()));
    ui->CountryLineEdit->setText(QString::fromStdString(controller->getCurrentPatient()->getAddress().getCountry()));
    ui->PostalCodeLineEdit->setText(QString::fromStdString(controller->getCurrentPatient()->getAddress().getPostalCode()));

    ui->DOBDateEdit->setDate(QDate(controller->getCurrentPatient()->getDateOfBirth().getYear(),
                                       controller->getCurrentPatient()->getDateOfBirth().getMonth(),
                                       controller->getCurrentPatient()->getDateOfBirth().getDay()));
    ui->AddedDateEdit->setDate(QDate(controller->getCurrentPatient()->getDateAddedToSystem().getYear(),
                                         controller->getCurrentPatient()->getDateAddedToSystem().getMonth(),
                                         controller->getCurrentPatient()->getDateAddedToSystem().getDay()));

    ui->CardNumberLineEdit->setText(QString::fromStdString(controller->getCurrentPatient()->getHealthCard().getNumber()));
    ui->CardExpirationDateEdit->setDate(QDate(controller->getCurrentPatient()->getHealthCard().getExpiry().getYear(),
                                                  controller->getCurrentPatient()->getHealthCard().getExpiry().getMonth(),
                                                  controller->getCurrentPatient()->getHealthCard().getExpiry().getDay()));

    ui->PatientNotesTextEdit->setText(QString::fromStdString(controller->getCurrentPatient()->getNotes()));
}

void MainWindow::showConsultationInfo(Consultation *pConsultation)
{
    //Switch to consultation tab and disable other tabs
    ui->DisplayTabsWidget->setTabEnabled(1, true);
    ui->DisplayTabsWidget->setCurrentIndex(1);
    ui->DisplayTabsWidget->setTabEnabled(0, false);
    ui->DisplayTabsWidget->setTabEnabled(2, false);

    //select the proper physician
    ui->PhysicianSelectComboBox->setCurrentIndex(ui->PhysicianSelectComboBox->findData(pConsultation->getConsultingPhys()->getId(), Qt::UserRole));

    ui->ReasonTextEdit->setText(QString::fromStdString(pConsultation->getReason()));

    ui->DiagnosisTextEdit->setText(QString::fromStdString(pConsultation->getDiagnosis()));

    ui->ConsultationCommentsTextEdit->setText(QString::fromStdString(pConsultation->getComments()));

    ui->ConsultationDateTimeEdit->setDateTime(QDateTime(QDate(pConsultation->getDate().getYear(),
                                                              pConsultation->getDate().getMonth(),
                                                              pConsultation->getDate().getDay()),
                                                        QTime(pConsultation->getTime().getHour(),
                                                              pConsultation->getTime().getMinute())));

    Consultation::ConsultationStatus cStat = pConsultation->getStatus();
    switch(cStat) {
    case Consultation::CSTAT_PENDING:
        ui->ConsultationStatusComboBox->setCurrentIndex(ui->ConsultationStatusComboBox->findText("Pending"));
    case Consultation::CSTAT_OCCURED:
        ui->ConsultationStatusComboBox->setCurrentIndex(ui->ConsultationStatusComboBox->findText("Occured"));
    case Consultation::CSTAT_COMPLETED:
        ui->ConsultationStatusComboBox->setCurrentIndex(ui->ConsultationStatusComboBox->findText("Completed"));
    case Consultation::CSTAT_ERROR:
        //handle error case here
        ui->ConsultationStatusComboBox->setCurrentIndex(ui->ConsultationStatusComboBox->findText("Pending"));
    }
}

void MainWindow::showFollowup()
{
    //Switch to followup tab and disable other tabs
    ui->DisplayTabsWidget->setTabEnabled(2, true);
    ui->DisplayTabsWidget->setCurrentIndex(2);
    ui->DisplayTabsWidget->setTabEnabled(0, false);
    ui->DisplayTabsWidget->setTabEnabled(1, false);

    //Hide buttons/fields for specific followup types
    ui->FollowupInfoLabel->hide();
    ui->FollowupInfoTextEdit->hide();
    ui->FollowupInfoLabel2->hide();
    ui->FollowupInfoTextEdit2->hide();
    ui->ReturnConsultationPushButton->hide();
}

void MainWindow::showMedicalTest(MedicalTest *pMedicalTest)
{
    showFollowup();

    Followup::FollowupStatus fStat = pMedicalTest->getStatus();
    switch(fStat) {
    case Followup::FSTAT_PENDING:
        ui->FollowupStatusComboBox->setCurrentIndex(ui->FollowupStatusComboBox->findText("Pending"));
    case Followup::FSTAT_OVERDUE:
        ui->FollowupStatusComboBox->setCurrentIndex(ui->FollowupStatusComboBox->findText("Overdue"));
    case Followup::FSTAT_RECEIVED:
        ui->FollowupStatusComboBox->setCurrentIndex(ui->FollowupStatusComboBox->findText("Received"));
    case Followup::FSTAT_COMPLETED:
        ui->FollowupStatusComboBox->setCurrentIndex(ui->FollowupStatusComboBox->findText("Completed"));
    case Followup::FSTAT_ERROR:
        //handle error case here
        ui->FollowupStatusComboBox->setCurrentIndex(ui->FollowupStatusComboBox->findText("Pending"));
    }

    ui->DueDateEdit->setDate(QDate(pMedicalTest->getDateDue().getYear(),
                                   pMedicalTest->getDateDue().getMonth(),
                                   pMedicalTest->getDateDue().getDay()));
    ui->ReceivedDateEdit->setDate(QDate(pMedicalTest->getDateReceived().getYear(),
                                   pMedicalTest->getDateReceived().getMonth(),
                                   pMedicalTest->getDateReceived().getDay()));
    ui->CompletedDateEdit->setDate(QDate(pMedicalTest->getDateCompleted().getYear(),
                                   pMedicalTest->getDateCompleted().getMonth(),
                                   pMedicalTest->getDateCompleted().getDay()));

    ui->FollowupInfoLabel->setText("Test Type:");
    ui->FollowupInfoLabel->show();
    ui->FollowupInfoTextEdit->setText(QString::fromStdString(pMedicalTest->getTestType()));
    ui->FollowupInfoTextEdit->show();

    ui->FollowupInfoLabel2->setText("Results:");
    ui->FollowupInfoLabel2->show();
    ui->FollowupInfoTextEdit2->setText(QString::fromStdString(pMedicalTest->getResults()));
    ui->FollowupInfoTextEdit2->show();
}

void MainWindow::showMedicationRenewal(MedicationRenewal *pMedicationRenewal)
{
    showFollowup();

    Followup::FollowupStatus fStat = pMedicationRenewal->getStatus();
    switch(fStat) {
    case Followup::FSTAT_PENDING:
        ui->FollowupStatusComboBox->setCurrentIndex(ui->FollowupStatusComboBox->findText("Pending"));
    case Followup::FSTAT_OVERDUE:
        ui->FollowupStatusComboBox->setCurrentIndex(ui->FollowupStatusComboBox->findText("Overdue"));
    case Followup::FSTAT_RECEIVED:
        ui->FollowupStatusComboBox->setCurrentIndex(ui->FollowupStatusComboBox->findText("Received"));
    case Followup::FSTAT_COMPLETED:
        ui->FollowupStatusComboBox->setCurrentIndex(ui->FollowupStatusComboBox->findText("Completed"));
    case Followup::FSTAT_ERROR:
        //handle error case here
        ui->FollowupStatusComboBox->setCurrentIndex(ui->FollowupStatusComboBox->findText("Pending"));
    }

    ui->DueDateEdit->setDate(QDate(pMedicationRenewal->getDateDue().getYear(),
                                   pMedicationRenewal->getDateDue().getMonth(),
                                   pMedicationRenewal->getDateDue().getDay()));
    ui->ReceivedDateEdit->setDate(QDate(pMedicationRenewal->getDateReceived().getYear(),
                                   pMedicationRenewal->getDateReceived().getMonth(),
                                   pMedicationRenewal->getDateReceived().getDay()));
    ui->CompletedDateEdit->setDate(QDate(pMedicationRenewal->getDateCompleted().getYear(),
                                   pMedicationRenewal->getDateCompleted().getMonth(),
                                   pMedicationRenewal->getDateCompleted().getDay()));

    ui->FollowupInfoLabel->setText("Medication:");
    ui->FollowupInfoLabel->show();
    ui->FollowupInfoTextEdit->setText(QString::fromStdString(pMedicationRenewal->getMedication()));
    ui->FollowupInfoTextEdit->show();
}

void MainWindow::showReferral(Referral *pReferral)
{
    showFollowup();

    Followup::FollowupStatus fStat = pReferral->getStatus();
    switch(fStat) {
    case Followup::FSTAT_PENDING:
        ui->FollowupStatusComboBox->setCurrentIndex(ui->FollowupStatusComboBox->findText("Pending"));
    case Followup::FSTAT_OVERDUE:
        ui->FollowupStatusComboBox->setCurrentIndex(ui->FollowupStatusComboBox->findText("Overdue"));
    case Followup::FSTAT_RECEIVED:
        ui->FollowupStatusComboBox->setCurrentIndex(ui->FollowupStatusComboBox->findText("Received"));
    case Followup::FSTAT_COMPLETED:
        ui->FollowupStatusComboBox->setCurrentIndex(ui->FollowupStatusComboBox->findText("Completed"));
    case Followup::FSTAT_ERROR:
        //handle error case here
        ui->FollowupStatusComboBox->setCurrentIndex(ui->FollowupStatusComboBox->findText("Pending"));
    }

    ui->DueDateEdit->setDate(QDate(pReferral->getDateDue().getYear(),
                                   pReferral->getDateDue().getMonth(),
                                   pReferral->getDateDue().getDay()));
    ui->ReceivedDateEdit->setDate(QDate(pReferral->getDateReceived().getYear(),
                                   pReferral->getDateReceived().getMonth(),
                                   pReferral->getDateReceived().getDay()));
    ui->CompletedDateEdit->setDate(QDate(pReferral->getDateCompleted().getYear(),
                                   pReferral->getDateCompleted().getMonth(),
                                   pReferral->getDateCompleted().getDay()));

    ui->FollowupInfoLabel->setText("Specialist Name:");
    ui->FollowupInfoLabel->show();
    ui->FollowupInfoTextEdit->setText(QString::fromStdString(pReferral->getSpecialistName()));
    ui->FollowupInfoTextEdit->show();

    ui->FollowupInfoLabel2->setText("Results:");
    ui->FollowupInfoLabel2->show();
    ui->FollowupInfoTextEdit2->setText(QString::fromStdString(pReferral->getResults()));
    ui->FollowupInfoTextEdit2->show();
}

void MainWindow::showResultantFollowup(ResultantFollowup *pResultantFollowup)
{
    showFollowup();

    Followup::FollowupStatus fStat = pResultantFollowup->getStatus();
    switch(fStat) {
    case Followup::FSTAT_PENDING:
        ui->FollowupStatusComboBox->setCurrentIndex(ui->FollowupStatusComboBox->findText("Pending"));
    case Followup::FSTAT_OVERDUE:
        ui->FollowupStatusComboBox->setCurrentIndex(ui->FollowupStatusComboBox->findText("Overdue"));
    case Followup::FSTAT_RECEIVED:
        ui->FollowupStatusComboBox->setCurrentIndex(ui->FollowupStatusComboBox->findText("Received"));
    case Followup::FSTAT_COMPLETED:
        ui->FollowupStatusComboBox->setCurrentIndex(ui->FollowupStatusComboBox->findText("Completed"));
    case Followup::FSTAT_ERROR:
        //handle error case here
        ui->FollowupStatusComboBox->setCurrentIndex(ui->FollowupStatusComboBox->findText("Pending"));
    }

    ui->DueDateEdit->setDate(QDate(pResultantFollowup->getDateDue().getYear(),
                                   pResultantFollowup->getDateDue().getMonth(),
                                   pResultantFollowup->getDateDue().getDay()));
    ui->ReceivedDateEdit->setDate(QDate(pResultantFollowup->getDateReceived().getYear(),
                                   pResultantFollowup->getDateReceived().getMonth(),
                                   pResultantFollowup->getDateReceived().getDay()));
    ui->CompletedDateEdit->setDate(QDate(pResultantFollowup->getDateCompleted().getYear(),
                                   pResultantFollowup->getDateCompleted().getMonth(),
                                   pResultantFollowup->getDateCompleted().getDay()));

    ui->FollowupInfoLabel->setText("Results:");
    ui->FollowupInfoLabel->show();
    ui->FollowupInfoTextEdit->setText(QString::fromStdString(pResultantFollowup->getResults()));
    ui->FollowupInfoTextEdit->show();
}

void MainWindow::showReturnConsultation(ReturnConsultation *pReturnConsultation)
{
    showFollowup();

    Followup::FollowupStatus fStat = pReturnConsultation->getStatus();
    switch(fStat) {
    case Followup::FSTAT_PENDING:
        ui->FollowupStatusComboBox->setCurrentIndex(ui->FollowupStatusComboBox->findText("Pending"));
    case Followup::FSTAT_OVERDUE:
        ui->FollowupStatusComboBox->setCurrentIndex(ui->FollowupStatusComboBox->findText("Overdue"));
    case Followup::FSTAT_RECEIVED:
        ui->FollowupStatusComboBox->setCurrentIndex(ui->FollowupStatusComboBox->findText("Received"));
    case Followup::FSTAT_COMPLETED:
        ui->FollowupStatusComboBox->setCurrentIndex(ui->FollowupStatusComboBox->findText("Completed"));
    case Followup::FSTAT_ERROR:
        //handle error case here
        ui->FollowupStatusComboBox->setCurrentIndex(ui->FollowupStatusComboBox->findText("Pending"));
    }

    ui->DueDateEdit->setDate(QDate(pReturnConsultation->getDateDue().getYear(),
                                   pReturnConsultation->getDateDue().getMonth(),
                                   pReturnConsultation->getDateDue().getDay()));
    ui->ReceivedDateEdit->setDate(QDate(pReturnConsultation->getDateReceived().getYear(),
                                   pReturnConsultation->getDateReceived().getMonth(),
                                   pReturnConsultation->getDateReceived().getDay()));
    ui->CompletedDateEdit->setDate(QDate(pReturnConsultation->getDateCompleted().getYear(),
                                   pReturnConsultation->getDateCompleted().getMonth(),
                                   pReturnConsultation->getDateCompleted().getDay()));

    ui->ReturnConsultationPushButton->show();
}

void MainWindow::populatePhysicians()
{
    string *pErrorString = NULL;
    pPhysicians = new vector<Physician *>();
    if (controller->getPhysicianList(pPhysicians, pErrorString)) {
        for (unsigned int i = 0 ; i < pPhysicians->size() ; i++) {
            ui->PhysicianSelectComboBox->addItem(QString::fromStdString(pPhysicians->at(i)->getLastName() + ", " + pPhysicians->at(i)->getFirstName()), pPhysicians->at(i)->getId());
        }
    }
}

void MainWindow::populatePatientTree()
{
    ui->PatientTreeWidget->clear();

    QTreeWidgetItem *pPatientWidget = new QTreeWidgetItem(ui->PatientTreeWidget);
    pPatientWidget->setText(0, QString::fromStdString(controller->getCurrentPatient()->getLastName() + string(", ") + controller->getCurrentPatient()->getFirstName()));
}
