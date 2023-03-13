#include <interchange.h>
#include <interchange/member.h>
#include "interchange/member.hxx"

namespace QInterchange {

	static Member* member;
	static char *unCopy, *pwCopy, *vCopy, *npCopy, *fpCopy;
	static interchange_member* mPtr;

	Member::Member(interchange_member data, QObject* parent) :
		QObject{parent}
	{
		member = this;

		if (data.username) m_userName = QString{data.username};
		else setUserName("");

		if (data.usernick) m_userNick = QString{data.usernick};
		else setUserNick("");

		if (data.password) m_password = QString{data.password};
		else setPassword("");

		if (data.expiration) m_expiration = QString{data.expiration};
		else setExpiration("");

		if (data.acl) m_acl = QString{data.acl};
		else setAcl("");

		if (data.mod_time) m_modTime = QString{data.mod_time};
		else setModTime("");

		if (data.s_nickname) m_sNickName = QString{data.s_nickname};
		else setSNickName("");

		if (data.company) m_company = QString{data.company};
		else setCompany("");

		if (data.fname) m_fName = QString{data.fname};
		else setFName("");

		if (data.lname) m_lName = QString{data.lname};
		else setLName("");

		if (data.address1) m_address1 = QString{data.address1};
		else setAddress1("");

		if (data.address2) m_address2 = QString{data.address2};
		else setAddress2("");

		if (data.address3) m_address3 = QString{data.address3};
		else setAddress3("");

		if (data.city) m_city = QString{data.city};
		else setCity("");

		if (data.state) m_state = QString{data.state};
		else setState("");

		if (data.zip) m_zip = QString{data.zip};
		else setZip("");

		if (data.country) m_country = QString{data.country};
		else setCountry("");

		if (data.phone_day) m_phoneDay = QString{data.phone_day};
		else setPhoneDay("");

		if (data.email) m_email = QString{data.email};
		else setEmail("");
	}

	Member::Member(QObject* parent) :
		QObject{parent},
		m_userName{""},
		m_userNick{""},
		m_password{""},
		m_expiration{""},
		m_acl{""},
		m_modTime{""},
		m_sNickName{""},
		m_company{""},
		m_fName{""},
		m_lName{""},
		m_address1{""},
		m_address2{""},
		m_address3{""},
		m_city{""},
		m_state{""},
		m_zip{""},
		m_country{""},
		m_phoneDay{""},
		m_email{""}
	{
		member = this;
	}

	void Member::newAccount(QString const& username,
			QString const& password, QString const& verify,
			QString const& failPage)
	{
		auto unData = username.toLatin1().constData();
		unCopy = (char*)malloc(strlen(unData) + 1);
		strcpy(unCopy, unData);
		auto pwData = password.toLatin1().constData();
		pwCopy = (char*)malloc(strlen(pwData) + 1);
		strcpy(pwCopy, pwData);
		auto vData = verify.toLatin1().constData();
		vCopy = (char*)malloc(strlen(vData) + 1);
		strcpy(vCopy, vData);
		auto fpData = failPage.toLatin1().constData();
		fpCopy = (char*)malloc(strlen(fpData) + 1);
		strcpy(fpCopy, fpData);
		interchange_member_newaccount(unCopy, pwCopy, vCopy, fpCopy,
			[](interchange_response* response) {
				free(unCopy);
				free(pwCopy);
				free(vCopy);
				free(fpCopy);
				member->emitCreation(QString{response->data});
				interchange_free_response(response);
			}, nullptr);
	}

	void Member::logIn(QString const& username, QString const& password,
			QString const& nextPage, QString const& failPage)
	{
		unCopy = (char*)malloc(username.size() + 1);
		strcpy(unCopy, username.toLatin1().constData());
		pwCopy = (char*)malloc(password.size() + 1);
		strcpy(pwCopy, password.toLatin1().constData());
		if (nextPage.isEmpty())
			npCopy = nullptr;
		else {
			npCopy = (char*)malloc(nextPage.size() + 1);
			strcpy(npCopy, nextPage.toLatin1().constData());
		}
		if (failPage.isEmpty())
			fpCopy = nullptr;
		else {
			fpCopy = (char*)malloc(failPage.size() + 1);
			strcpy(fpCopy, failPage.toLatin1().constData());
		}
		interchange_member_login(unCopy, pwCopy, npCopy, fpCopy,
				[](interchange_response* response) {
			free(unCopy);
			free(pwCopy);
			if (npCopy) free(npCopy);
			if (fpCopy) free(fpCopy);
			member->emitLogin(QString{response->data});
			interchange_free_response(response);
		}, nullptr);
	}

	void Member::setAccount(QString const& firstName,
			QString const& lastName, QString const& address1,
			QString const& address2, QString const& city,
			QString const& state, QString const& zip,
			QString const& email, QString const& phoneDay)
	{
		auto fnData = firstName.toLatin1().constData();
		auto fnCopy = (char*)malloc(strlen(fnData) + 1);
		strcpy(fnCopy, fnData);
		auto lnData = lastName.toLatin1().constData();
		auto lnCopy = (char*)malloc(strlen(lnData) + 1);
		strcpy(lnCopy, lnData);
		auto a1Data = address1.toLatin1().constData();
		auto a1Copy = (char*)malloc(strlen(a1Data) + 1);
		strcpy(a1Copy, a1Data);
		auto a2Data = address2.toLatin1().constData();
		auto a2Copy = (char*)malloc(strlen(a2Data) + 1);
		strcpy(a2Copy, a2Data);
		auto cData = city.toLatin1().constData();
		auto cCopy = (char*)malloc(strlen(cData) + 1);
		strcpy(cCopy, cData);
		auto sData = state.toLatin1().constData();
		auto sCopy = (char*)malloc(strlen(sData) + 1);
		strcpy(sCopy, sData);
		auto zData = zip.toLatin1().constData();
		auto zCopy = (char*)malloc(strlen(zData) + 1);
		strcpy(zCopy, zData);
		auto emData = email.toLatin1().constData();
		auto emCopy = (char*)malloc(strlen(emData) + 1);
		strcpy(emCopy, emData);
		auto pdData = phoneDay.toLatin1().constData();
		auto pdCopy = (char*)malloc(strlen(pdData) + 1);
		strcpy(pdCopy, pdData);
		interchange_member m = {
			.fname = fnCopy,
			.lname = lnCopy,
			.address1 = a1Copy,
			.address2 = a2Copy,
			.city = cCopy,
			.state = sCopy,
			.zip = zCopy,
			.phone_day = pdCopy,
			.email = emCopy
		};
		mPtr = &m;
		interchange_member_setaccount(mPtr,
				[](interchange_response* response) {
			free(mPtr->fname);
			free(mPtr->lname);
			free(mPtr->address1);
			free(mPtr->address2);
			free(mPtr->city);
			free(mPtr->state);
			free(mPtr->zip);
			free(mPtr->phone_day);
			free(mPtr->email);
			member->emitSetAccount(QString{response->data});
			interchange_free_response(response);
		});
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

	void Member::account()
	{
		interchange_member_account([](interchange_response* response) {
			member->emitAccount(QString{response->data});
			interchange_free_response(response);
		});
	}

	void Member::changePassword(QString const& passwordOld, QString const& password,
			QString const& verify)
	{
		interchange_member_changepassword(passwordOld.toLatin1().constData(),
				password.toLatin1().constData(),
				verify.toLatin1().constData());
	}

	void Member::logOut()
	{
		interchange_member_logout();
	}

	void Member::emitCreation(QString const& response)
	{
		emit created(response);
	}

	void Member::emitLogin(QString const& response)
	{
		emit loggedIn(response);
	}

	void Member::emitSetAccount(QString const& response)
	{
		emit setAccount(response);
	}

	void Member::emitAccount(QString const& response)
	{
		emit gotAccount(response);
	}
}
