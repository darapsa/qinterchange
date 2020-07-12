#include <cstddef>
#include <icclient/client.h>
#include "qicclient/member.hxx"

namespace QICClient {

	void Member::logIn(QString const& username, QString const& password,
			QString const& successPage, QString const& nextPage,
			QString const& failPage,
			size_t (*handler)(void*, size_t, size_t, void*))
	{
		m_data = icclient_member_login(username.toLatin1().constData(),
				password.toLatin1().constData(),
				successPage.toLatin1().constData(),
				nextPage.toLatin1().constData(),
				failPage.toLatin1().constData(),
				handler);
		if (m_data->username && m_userName != m_data->username) {
			m_userName = QString{m_data->username};
			emit userNameChanged();
		} else if (m_userName != "") {
			m_userName = "";
			emit userNameChanged();
		}
		if (m_data->usernick && m_userNick != m_data->usernick) {
			m_userNick = QString{m_data->usernick};
			emit userNickChanged();
		} else if (m_userNick != "") {
			m_userNick = "";
			emit userNickChanged();
		}
		if (m_data->password && m_password != m_data->password) {
			m_password = QString{m_data->password};
			emit passwordChanged();
		} else if (m_password != "") {
			m_password = "";
			emit passwordChanged();
		}
		if (m_data->expiration && m_expiration != m_data->expiration) {
			m_expiration = QString{m_data->expiration};
			emit expirationChanged();
		} else if (m_expiration != "") {
			m_expiration = "";
			emit expirationChanged();
		}
		if (m_data->acl && m_acl != m_data->acl) {
			m_acl = QString{m_data->acl};
			emit aclChanged();
		} else if (m_acl != "") {
			m_acl = "";
			emit aclChanged();
		}
		if (m_data->mod_time && m_modTime != m_data->mod_time) {
			m_modTime = QString{m_data->mod_time};
			emit modTimeChanged();
		} else if (m_modTime != "") {
			m_modTime = "";
			emit modTimeChanged();
		}
		if (m_data->s_nickname && m_sNickName != m_data->s_nickname) {
			m_sNickName = QString{m_data->s_nickname};
			emit sNickNameChanged();
		} else if (m_sNickName != "") {
			m_sNickName = "";
			emit sNickNameChanged();
		}
		if (m_data->company && m_company != m_data->company) {
			m_company = QString{m_data->company};
			emit companyChanged();
		} else if (m_company != "") {
			m_company = "";
			emit companyChanged();
		}
		if (m_data->fname && m_fName != m_data->fname) {
			m_fName = QString{m_data->fname};
			emit fNameChanged();
		} else if (m_fName != "") {
			m_fName = "";
			emit fNameChanged();
		}
		if (m_data->lname && m_lName != m_data->lname) {
			m_lName = QString{m_data->lname};
			emit lNameChanged();
		} else if (m_lName != "") {
			m_lName = "";
			emit lNameChanged();
		}
		if (m_data->address1 && m_address1 != m_data->address1) {
			m_address1 = QString{m_data->address1};
			emit address1Changed();
		} else if (m_address1 != "") {
			m_address1 = "";
			emit address1Changed();
		}
		if (m_data->address2 && m_address2 != m_data->address2) {
			m_address2 = QString{m_data->address2};
			emit address2Changed();
		} else if (m_address2 != "") {
			m_address2 = "";
			emit address2Changed();
		}
		if (m_data->address3 && m_address3 != m_data->address3) {
			m_address3 = QString{m_data->address3};
			emit address3Changed();
		} else if (m_address3 != "") {
			m_address3 = "";
			emit address3Changed();
		}
		if (m_data->city && m_city != m_data->city) {
			m_city = QString{m_data->city};
			emit cityChanged();
		} else if (m_city != "") {
			m_city = "";
			emit cityChanged();
		}
		if (m_data->state && m_state != m_data->state) {
			m_state = QString{m_data->state};
			emit stateChanged();
		} else if (m_state != "") {
			m_state = "";
			emit stateChanged();
		}
		if (m_data->zip && m_zip != m_data->zip) {
			m_zip = QString{m_data->zip};
			emit zipChanged();
		} else if (m_zip != "") {
			m_zip = "";
			emit zipChanged();
		}
		if (m_data->country && m_country != m_data->country) {
			m_country = QString{m_data->country};
			emit countryChanged();
		} else if (m_country != "") {
			m_country = "";
			emit countryChanged();
		}
		if (m_data->phone_day && m_phoneDay != m_data->phone_day) {
			m_phoneDay = QString{m_data->phone_day};
			emit phoneDayChanged();
		} else if (m_phoneDay != "") {
			m_phoneDay = "";
			emit phoneDayChanged();
		}
		if (m_data->email && m_email != m_data->email) {
			m_email = QString{m_data->email};
			emit emailChanged();
		} else if (m_email != "") {
			m_email = "";
			emit emailChanged();
		}
	}

	void Member::setUserName(QString const& userName)
	{
		if (m_userName != userName) {
			m_userName = userName;
			emit userNameChanged();
		}
	}

	void Member::setUserNick(QString const& userNick)
	{
		if (m_userNick != userNick) {
			m_userNick = userNick;
			emit userNickChanged();
		}
	}

	void Member::setPassword(QString const& password)
	{
		if (m_password != password) {
			m_password = password;
			emit passwordChanged();
		}
	}

	void Member::setExpiration(QString const& expiration)
	{
		if (m_expiration != expiration) {
			m_expiration = expiration;
			emit expirationChanged();
		}
	}

	void Member::setAcl(QString const& acl)
	{
		if (m_acl != acl) {
			m_acl = acl;
			emit aclChanged();
		}
	}

	void Member::setModTime(QString const& modTime)
	{
		if (m_modTime != modTime) {
			m_modTime = modTime;
			emit modTimeChanged();
		}
	}

	void Member::setSNickName(QString const& sNickName)
	{
		if (m_sNickName != sNickName) {
			m_sNickName = sNickName;
			emit sNickNameChanged();
		}
	}

	void Member::setCompany(QString const& company)
	{
		if (m_company != company) {
			m_company = company;
			emit companyChanged();
		}
	}

	void Member::setFName(QString const& fName)
	{
		if (m_fName != fName) {
			m_fName = fName;
			emit fNameChanged();
		}
	}

	void Member::setLName(QString const& lName)
	{
		if (m_lName != lName) {
			m_lName = lName;
			emit lNameChanged();
		}
	}

	void Member::setAddress1(QString const& address1)
	{
		if (m_address1 != address1) {
			m_address1 = address1;
			emit address1Changed();
		}
	}

	void Member::setAddress2(QString const& address2)
	{
		if (m_address2 != address2) {
			m_address2 = address2;
			emit address2Changed();
		}
	}

	void Member::setAddress3(QString const& address3)
	{
		if (m_address3 != address3) {
			m_address3 = address3;
			emit address3Changed();
		}
	}

	void Member::setCity(QString const& city)
	{
		if (m_city != city) {
			m_city = city;
			emit cityChanged();
		}
	}

	void Member::setState(QString const& state)
	{
		if (m_state != state) {
			m_state = state;
			emit stateChanged();
		}
	}

	void Member::setZip(QString const& zip)
	{
		if (m_zip != zip) {
			m_zip = zip;
			emit zipChanged();
		}
	}

	void Member::setCountry(QString const& country)
	{
		if (m_country != country) {
			m_country = country;
			emit countryChanged();
		}
	}

	void Member::setPhoneDay(QString const& phoneDay)
	{
		if (m_phoneDay != phoneDay) {
			m_phoneDay = phoneDay;
			emit phoneDayChanged();
		}
	}

	void Member::setEmail(QString const& email)
	{
		if (m_email != email) {
			m_email = email;
			emit emailChanged();
		}
	}

	void Member::logOut()
	{
		icclient_member_logout(m_data);
	}

}
