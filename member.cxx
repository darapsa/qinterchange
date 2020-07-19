#include <cstddef>
#include <icclient/member.h>
#include "qicclient/member.hxx"

namespace QICClient {

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

	void Member::setData(icclient_member* data)
	{
		if (data && data->username && m_userName != data->username) {
			m_userName = QString{data->username};
			emit userNameChanged();
		} else setUserName("");

		if (data && data->usernick && m_userNick != data->usernick) {
			m_userNick = QString{data->usernick};
			emit userNickChanged();
		} else setUserNick("");

		if (data && data->password && m_password != data->password) {
			m_password = QString{data->password};
			emit passwordChanged();
		} else setPassword("");

		if (data && data->expiration && m_expiration != data->expiration) {
			m_expiration = QString{data->expiration};
			emit expirationChanged();
		} else setExpiration("");

		if (data && data->acl && m_acl != data->acl) {
			m_acl = QString{data->acl};
			emit aclChanged();
		} else setAcl("");

		if (data && data->mod_time && m_modTime != data->mod_time) {
			m_modTime = QString{data->mod_time};
			emit modTimeChanged();
		} else setModTime("");

		if (data && data->s_nickname && m_sNickName != data->s_nickname) {
			m_sNickName = QString{data->s_nickname};
			emit sNickNameChanged();
		} else setSNickName("");

		if (data && data->company && m_company != data->company) {
			m_company = QString{data->company};
			emit companyChanged();
		} else setCompany("");

		if (data && data->fname && m_fName != data->fname) {
			m_fName = QString{data->fname};
			emit fNameChanged();
		} else setFName("");

		if (data && data->lname && m_lName != data->lname) {
			m_lName = QString{data->lname};
			emit lNameChanged();
		} else setLName("");

		if (data && data->address1 && m_address1 != data->address1) {
			m_address1 = QString{data->address1};
			emit address1Changed();
		} else setAddress1("");

		if (data && data->address2 && m_address2 != data->address2) {
			m_address2 = QString{data->address2};
			emit address2Changed();
		} else setAddress2("");

		if (data && data->address3 && m_address3 != data->address3) {
			m_address3 = QString{data->address3};
			emit address3Changed();
		} else setAddress3("");

		if (data && data->city && m_city != data->city) {
			m_city = QString{data->city};
			emit cityChanged();
		} else setCity("");

		if (data && data->state && m_state != data->state) {
			m_state = QString{data->state};
			emit stateChanged();
		} else setState("");

		if (data && data->zip && m_zip != data->zip) {
			m_zip = QString{data->zip};
			emit zipChanged();
		} else setZip("");

		if (data && data->country && m_country != data->country) {
			m_country = QString{data->country};
			emit countryChanged();
		} else setCountry("");

		if (data && data->phone_day && m_phoneDay != data->phone_day) {
			m_phoneDay = QString{data->phone_day};
			emit phoneDayChanged();
		} else setPhoneDay("");

		if (data && data->email && m_email != data->email) {
			m_email = QString{data->email};
			emit emailChanged();
		} else setEmail("");

		if (m_data != data) m_data = data;
	}

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

	void Member::account(QString const& firstName, QString const& lastName,
			QString const& address1, QString const& address2,
			QString const& city, QString const& state, QString const& zip,
			QString const& email, QString const& phoneDay)
	{
		icclient_member_account(firstName.toLatin1().constData(),
				lastName.toLatin1().constData(),
				address1.toLatin1().constData(),
				address2.toLatin1().constData(),
				city.toLatin1().constData(), state.toLatin1().constData(),
				zip.toLatin1().constData(), email.toLatin1().constData(),
				phoneDay.toLatin1().constData());
	}

	void Member::changePassword(QString const& passwordOld, QString const& password,
			QString const& verify)
	{
		icclient_member_changepassword(passwordOld.toLatin1().constData(),
				password.toLatin1().constData(),
				verify.toLatin1().constData());
	}

	void Member::logOut()
	{
		icclient_member_logout(m_data);
		setData(nullptr);
	}

}
