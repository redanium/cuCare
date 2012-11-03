#ifndef REQUEST_H
#define REQUEST_H


#include "commsinclude.h"
#include "clientsocket.h"
#include "messagegenerator.h"
#include <QVariant>
#include "messageparser.h"

class Request {

private:
    quint16 serverPort;
    QHostAddress serverIPAddress;

public:
    Request(string serverIPAddressParam, quint16 serverPortParam);
    ~Request();



    /* ***Server Interface Functions***

       The following functions deal with sending information to, and recieving information from, server.
       They all follow the same rules for RETURN values:
        0: Success
       -1: Bad input
       -2: Network error
       -3: Server error

       If an error occurs, a message will be placed into pErrString, a string pointer which all of these functions take.
      */

    //Creation functions
    int createPhysician(string *pErrString, Physician *pInputPhysician, int *pUid);
    int createAdminAssistant(string *pErrString, AdminAssistant *pInputAdminAssistant, int *pUid);
    int createSysAdmin(string *pErrString, SysAdmin *pInputSysAdmin, int *pUid);
    int createPatient(string *pErrString, Patient *pInputPatient, int physicianId, int *pUid);
    int createConsultation(string *pErrString, Consultation *pInputConsultation, int physicianId, int patientId, int *pUid);
    int createReferral(string *pErrString, Referral *pInputReferral, int consultationId, int **ppUid);
    int createMedicalTest(string *pErrString, MedicalTest *pInputMedicalTest, int consultationId, int **ppUid);
    int createReturnConsultation(string *pErrString, ReturnConsultation *pInputReturnConsultation, int consultationId, int nextConsultationId, int *pUid);
    int createMedicationRenewal(string *pErrString, MedicationRenewal *pInputMedicationRenewal, int consultationId, int *pUid);

    //Modification functions
    int pushUser(string *pErrString, User inputUser);
    int pushPatient(string *pErrString, Patient inputPatient, int physicianId);
    int pushConsultation(string *pErrString, Consultation inputPatient, int physicianId, int patientId);
    int pushReferral(string *pErrString, Referral inputReferral, int consultationId);
    int pushMedicalTest(string *pErrString, MedicalTest inputMedicalTest, int physicianId);
    int pushReturnConsultation(string *pErrString, ReturnConsultation inputReturnConsultation, int physicianId, int nextConsultationId);
    int pushMedicationRenewal(string *pErrString, MedicationRenewal inputMedicationRenewal, int physicianId);

    //Object retrieval functions
    int pullPhysician(string *pErrString, Physician *pPhysicianValues, UserFilter inputFilter, vector<Physician*> *pOutputPhysicians);
    int pullAdminAssistant(string *pErrString, AdminAssistant *pPhysicianValues, UserFilter inputFilter, vector<AdminAssistant*> *pOutputAdminAssistants);
    int pullSysAdmin(string *pErrString, SysAdmin *pSysAdminValues, UserFilter inputFilter, vector<SysAdmin*> *pOutputSysAdmins);
    int pullPatient(string *pErrString, Patient *pPatientValues, PatientFilter inputFilter, vector<SysAdmin*> *pOutputPatients);
    int pullConsultation(string *pErrString, Consultation *pConsultationValues, ConsultationFilter inputFilter, vector<Consultation*> *pOutputConsultations);
    int pullReferral(string *pErrString, Referral *pReferralValues, ReferralFilter inputFilter, vector<Referral*> *pOutputReferral);
    int pullMedicalTest(string *pErrString, MedicalTest *pMedicalTestValues, MedicalTestFilter inputFilter, vector<MedicalTest*> *pOutputMedicalTests);
    int pullReturnConsultation(string *pErrString, ReturnConsultation *pReturnConsultationValues, ReturnConsultationFilter inputFilter, vector<ReturnConsultation*> *pOutputReturnConsultation);
    int pullMedicationRenewal(string *pErrString, MedicationRenewal *pMedicationRenewalValues, MedicationRenewalsFilter inputFilter, vector<MedicalTest*> *pOutputMedicationRenewal);


private:
    QHostAddress getServerAddress();
    quint16 getServerPort();
};

#endif // REQUEST_H
