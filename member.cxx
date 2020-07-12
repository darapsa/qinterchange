#include <cstddef>
#include <icclient/client.h>
#include "qicclient/member.hxx"

namespace QICClient {

	void Member::logIn(QString const& username, QString const& password,
			QString const& successPage, QString const& nextPage,
			QString const& failPage,
			size_t (*handler)(void*, size_t, size_t, void*))
	{
		setData(icclient_member_login(username.toLatin1().constData(),
					password.toLatin1().constData(),
					successPage.toLatin1().constData(),
					nextPage.toLatin1().constData(),
					failPage.toLatin1().constData(),
					handler));
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

	void Member::setData(icclient_member* member)
	{
		if (member->username && m_userName != member->username) {
			m_userName = QString{member->username};
			emit userNameChanged();
		} else if (m_userName != "") {
			m_userName = "";
			emit userNameChanged();
		}
		if (member->usernick && m_userNick != member->usernick) {
			m_userNick = QString{member->usernick};
			emit userNickChanged();
		} else if (m_userNick != "") {
			m_userNick = "";
			emit userNickChanged();
		}
		if (member->password && m_password != member->password) {
			m_password = QString{member->password};
			emit passwordChanged();
		} else if (m_password != "") {
			m_password = "";
			emit passwordChanged();
		}
		if (member->expiration && m_expiration != member->expiration) {
			m_expiration = QString{member->expiration};
			emit expirationChanged();
		} else if (m_expiration != "") {
			m_expiration = "";
			emit expirationChanged();
		}
		if (member->acl && m_acl != member->acl) {
			m_acl = QString{member->acl};
			emit aclChanged();
		} else if (m_acl != "") {
			m_acl = "";
			emit aclChanged();
		}
		if (member->mod_time && m_modTime != member->mod_time) {
			m_modTime = QString{member->mod_time};
			emit modTimeChanged();
		} else if (m_modTime != "") {
			m_modTime = "";
			emit modTimeChanged();
		}
		if (member->s_nickname && m_sNickName != member->s_nickname) {
			m_sNickName = QString{member->s_nickname};
			emit sNickNameChanged();
		} else if (m_sNickName != "") {
			m_sNickName = "";
			emit sNickNameChanged();
		}
		if (member->company && m_company != member->company) {
			m_company = QString{member->company};
			emit companyChanged();
		} else if (m_company != "") {
			m_company = "";
			emit companyChanged();
		}
		if (member->fname && m_fName != member->fname) {
			m_fName = QString{member->fname};
			emit fNameChanged();
		} else if (m_fName != "") {
			m_fName = "";
			emit fNameChanged();
		}
		if (member->lname && m_lName != member->lname) {
			m_lName = QString{member->lname};
			emit lNameChanged();
		} else if (m_lName != "") {
			m_lName = "";
			emit lNameChanged();
		}
		if (member->address1 && m_address1 != member->address1) {
			m_address1 = QString{member->address1};
			emit address1Changed();
		} else if (m_address1 != "") {
			m_address1 = "";
			emit address1Changed();
		}
		if (member->address2 && m_address2 != member->address2) {
			m_address2 = QString{member->address2};
			emit address2Changed();
		} else if (m_address2 != "") {
			m_address2 = "";
			emit address2Changed();
		}
		if (member->address3 && m_address3 != member->address3) {
			m_address3 = QString{member->address3};
			emit address3Changed();
		} else if (m_address3 != "") {
			m_address3 = "";
			emit address3Changed();
		}
		if (member->city && m_city != member->city) {
			m_city = QString{member->city};
			emit cityChanged();
		} else if (m_city != "") {
			m_city = "";
			emit cityChanged();
		}
		if (member->state && m_state != member->state) {
			m_state = QString{member->state};
			emit stateChanged();
		} else if (m_state != "") {
			m_state = "";
			emit stateChanged();
		}
		if (member->zip && m_zip != member->zip) {
			m_zip = QString{member->zip};
			emit zipChanged();
		} else if (m_zip != "") {
			m_zip = "";
			emit zipChanged();
		}
		if (member->country && m_country != member->country) {
			m_country = QString{member->country};
			emit countryChanged();
		} else if (m_country != "") {
			m_country = "";
			emit countryChanged();
		}
		if (member->phone_day && m_phoneDay != member->phone_day) {
			m_phoneDay = QString{member->phone_day};
			emit phoneDayChanged();
		} else if (m_phoneDay != "") {
			m_phoneDay = "";
			emit phoneDayChanged();
		}
		if (member->email && m_email != member->email) {
			m_email = QString{member->email};
			emit emailChanged();
		} else if (m_email != "") {
			m_email = "";
			emit emailChanged();
		}
	}

	void Member::logOut()
	{
		icclient_member_logout(m_data);
	}

}
