#include <cstddef>
#include <icclient/client.h>
#include "qicclient/user.hxx"

namespace QICClient {

	void User::setUserName(QString const& UserName)
	{
		if (m_userName != UserName) {
			m_userName = UserName;
			emit userNameChanged();
		}
	}

	void User::setUserNick(QString const& UserNick)
	{
		if (m_userNick != UserNick) {
			m_userNick = UserNick;
			emit userNickChanged();
		}
	}

	void User::setPassword(QString const& password)
	{
		if (m_password != password) {
			m_password = password;
			emit passwordChanged();
		}
	}

	void User::setExpiration(QString const& expiration)
	{
		if (m_expiration != expiration) {
			m_expiration = expiration;
			emit expirationChanged();
		}
	}

	void User::setAcl(QString const& acl)
	{
		if (m_acl != acl) {
			m_acl = acl;
			emit aclChanged();
		}
	}

	void User::setModTime(QString const& modTime)
	{
		if (m_modTime != modTime) {
			m_modTime = modTime;
			emit modTimeChanged();
		}
	}

	void User::setSNickName(QString const& sNickName)
	{
		if (m_sNickName != sNickName) {
			m_sNickName = sNickName;
			emit sNickNameChanged();
		}
	}

	void User::setCompany(QString const& company)
	{
		if (m_company != company) {
			m_company = company;
			emit companyChanged();
		}
	}

	void User::setFName(QString const& fName)
	{
		if (m_fName != fName) {
			m_fName = fName;
			emit fNameChanged();
		}
	}

	void User::setLName(QString const& lName)
	{
		if (m_lName != lName) {
			m_lName = lName;
			emit lNameChanged();
		}
	}

	void User::setAddress1(QString const& address1)
	{
		if (m_address1 != address1) {
			m_address1 = address1;
			emit address1Changed();
		}
	}

	void User::setAddress2(QString const& address2)
	{
		if (m_address2 != address2) {
			m_address2 = address2;
			emit address2Changed();
		}
	}

	void User::setAddress3(QString const& address3)
	{
		if (m_address3 != address3) {
			m_address3 = address3;
			emit address3Changed();
		}
	}

	void User::setCity(QString const& city)
	{
		if (m_city != city) {
			m_city = city;
			emit cityChanged();
		}
	}

	void User::setState(QString const& state)
	{
		if (m_state != state) {
			m_state = state;
			emit stateChanged();
		}
	}

	void User::setZip(QString const& zip)
	{
		if (m_zip != zip) {
			m_zip = zip;
			emit zipChanged();
		}
	}

	void User::setCountry(QString const& country)
	{
		if (m_country != country) {
			m_country = country;
			emit countryChanged();
		}
	}

	void User::setPhoneDay(QString const& phoneDay)
	{
		if (m_phoneDay != phoneDay) {
			m_phoneDay = phoneDay;
			emit phoneDayChanged();
		}
	}

	void User::setEmail(QString const& email)
	{
		if (m_email != email) {
			m_email = email;
			emit emailChanged();
		}
	}

	void User::update(icclient_member* member)
	{
		if (member->username)
			m_userName = QString{member->username};
		else
			m_userName = "";
		if (member->usernick)
			m_userNick = QString{member->usernick};
		else
			m_userNick = "";
		if (member->fname)
			m_fName = QString{member->fname};
		else
			m_fName = "";
		if (member->lname)
			m_lName = QString{member->lname};
		else
			m_lName = "";
		if (member->address1)
			m_address1 = QString{member->address1};
		else
			m_address1 = "";
		if (member->address2)
			m_address2 = QString{member->address2};
		else
			m_address2 = "";
		if (member->address3)
			m_address3 = QString{member->address3};
		else
			m_address3 = "";
		if (member->city)
			m_city = QString{member->city};
		else
			m_city = "";
		if (member->state)
			m_state = QString{member->state};
		else
			m_state = "";
		if (member->zip)
			m_zip = QString{member->zip};
		else
			m_zip = "";
		if (member->country)
			m_country = QString{member->country};
		else
			m_country = "";
		if (member->phone_day)
			m_phoneDay = QString{member->phone_day};
		else
			m_phoneDay = "";
		if (member->email)
			m_email = QString{member->email};
		else
			m_email = "";

		emit userNameChanged();
		emit userNickChanged();
		emit passwordChanged();
		emit expirationChanged();
		emit aclChanged();
		emit modTimeChanged();
		emit sNickNameChanged();
		emit companyChanged();
		emit fNameChanged();
		emit lNameChanged();
		emit address1Changed();
		emit address2Changed();
		emit address3Changed();
		emit cityChanged();
		emit stateChanged();
		emit zipChanged();
		emit countryChanged();
		emit phoneDayChanged();
		emit emailChanged();
	}

}
