// COMP 3004 FALL 2012
// Assignment 2: cuCare Prototype
// Team: The Four Puppeteers
// Contributing Editors: Sergey Vershinin
//
// MasterController.h - Declaration of base class MasterController
// Member functions are defined in MasterController.cpp

#ifndef MASTERCONTROLLER_H
#define MASTERCONTROLLER_H

#include "../CuCareModel/ModelFiles.h"
#include "../CuCareCommunications/Communications/request.h"
#include <string>
#include <vector>

class MasterController {
public:

    // Access Control

    enum AccessControlStatus
    {
        AC_FAILED,
        AC_LOGGED_OUT,
        AC_LOGGED_IN_AS_PHYSICIAN,
        AC_LOGGED_IN_AS_ADMINASSISTANT,
        AC_LOGGED_IN_AS_SYSADMIN
    };

    AccessControlStatus loginUser(string username, string *pErrString);
    AccessControlStatus loginStatus();
    AccessControlStatus logout();

    // Patients

    // createPatient() Parameters:
    // pInputPatient - a ptr to a Patient object with the new data (do not delete, this will get assigned to currentPatient)
    // physicianId - the UID of the Patient's Physician
    // pErrString - a ptr to a string that will be populated with the error message (if any)
    bool createPatient(Patient* pInputPatient, int physicianId, string *pErrString);

    bool modifyPatient(Patient* pInputPatient, int physicianId, string *pErrString);

    bool getPatientList(vector<Patient *> *pResults, string *pErrString); // no filter

//    bool getPatientList(Patient* pPatientValues, PatientFilter patientFilter, vector<Patient*>* pResults); // filtered, will not populate consultations or followups

    // getFullPatient() Notes:
    // ? gets the full record for the patient, and points pCurrentPatient
    // ? assumes that it is being passed a pointer to a "shallow" patient that comes from a getPatientList() call
    bool getFullPatient(Patient* newCurrentPatient, string *pErrString); // must supply valid UID

    Patient* getCurrentPatient();   // returns a pointer to the currently selected patient
                                    // NULL ptr if no patient has yet been selected

    // Consultations

    bool createConsultation(Consultation* pInputConsultation, string *pErrString);
    bool modifyConsultation(Consultation* pInputConsultation, string *pErrString);

    // Follow-ups

    bool createFollowup(Followup* pInputFollowup, string *pErrString);
    bool modifyFollowup(Followup* pInputFollowup, string *pErrString);

    // Physicians

    bool getPhysicianList(vector<Physician*> *pResults, string *pErrString);

private:

    AccessControlStatus authorize(User* user);

    // Stores the user object for access control
    // Set to NULL if not logged-in
    User* pCurrentUser;

    AccessControlStatus status;

    // Stores the data for the currently selected patient
    // Set to NULL if a patient has not yet been selected
    Patient* pCurrentPatient;
};


#endif // MASTERCONTROLLER_H

// EOF
