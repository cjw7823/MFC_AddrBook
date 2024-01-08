#pragma once
#include <afx.h>

class CUserData :
    public CObject
{
public:
    CUserData(CString name, CString phone)
    {
        m_strName = name;
        m_strPhone = phone;
    }

    CUserData(const CUserData& rhs) 
    { 
        this->m_strName = rhs.m_strName;
        this->m_strPhone = rhs.m_strPhone;
    }

    CString GetName() { return m_strName; }
    CString GetPhone() { return m_strPhone; }

    bool operator==(CUserData otherData)
    {
        if (this->m_strName == otherData.m_strName && this->m_strPhone == otherData.m_strPhone)
            return true;

        return false;
    }

private:
    CString m_strName;
    CString m_strPhone;
};

