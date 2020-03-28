#include <cstddef>
#include <icclient/client.h>
#include "qicclient/user.hxx"

namespace ICClient {

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

	void User::update(icclient_user* user)
	{
		if (user->username)
			m_userName = QString{user->username};
		else
			m_userName = "";
		if (user->usernick)
			m_userNick = QString{user->usernick};
		else
			m_userNick = "";
		if (user->fname)
			m_fName = QString{user->fname};
		else
			m_fName = "";
		if (user->lname)
			m_lName = QString{user->lname};
		else
			m_lName = "";
		if (user->address1)
			m_address1 = QString{user->address1};
		else
			m_address1 = "";
		if (user->address2)
			m_address2 = QString{user->address2};
		else
			m_address2 = "";
		if (user->address3)
			m_address3 = QString{user->address3};
		else
			m_address3 = "";
		if (user->city)
			m_city = QString{user->city};
		else
			m_city = "";
		if (user->state)
			m_state = QString{user->state};
		else
			m_state = "";
		if (user->zip)
			m_zip = QString{user->zip};
		else
			m_zip = "";
		if (user->country)
			m_country = QString{user->country};
		else
			m_country = "";
		if (user->phone_day)
			m_phoneDay = QString{user->phone_day};
		else
			m_phoneDay = "";
		if (user->email)
			m_email = QString{user->email};
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
