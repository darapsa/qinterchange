#ifndef QICCLIENT_MEMBER_HXX
#define QICCLIENT_MEMBER_HXX

#include <QObject>
#include <icclient/member.h>

struct icclient_member;

namespace QICClient {

	class Member : public QObject
	{
		Q_OBJECT
		Q_PROPERTY(QString userName READ userName WRITE setUserName NOTIFY userNameChanged)
		Q_PROPERTY(QString userNick READ userNick WRITE setUserNick NOTIFY userNickChanged)
		Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)
		Q_PROPERTY(QString expiration READ expiration WRITE setExpiration NOTIFY expirationChanged)
		Q_PROPERTY(QString acl READ acl WRITE setAcl NOTIFY aclChanged)
		Q_PROPERTY(QString modTime READ modTime WRITE setModTime NOTIFY modTimeChanged)
		Q_PROPERTY(QString sNickName READ sNickName WRITE setSNickName NOTIFY sNickNameChanged)
		Q_PROPERTY(QString company READ company WRITE setCompany NOTIFY companyChanged)
		Q_PROPERTY(QString fName READ fName WRITE setFName NOTIFY fNameChanged)
		Q_PROPERTY(QString lName READ lName WRITE setLName NOTIFY lNameChanged)
		Q_PROPERTY(QString address1 READ address1 WRITE setAddress1 NOTIFY address1Changed)
		Q_PROPERTY(QString address2 READ address2 WRITE setAddress2 NOTIFY address2Changed)
		Q_PROPERTY(QString address3 READ address3 WRITE setAddress3 NOTIFY address3Changed)
		Q_PROPERTY(QString city READ city WRITE setCity NOTIFY cityChanged)
		Q_PROPERTY(QString state READ state WRITE setState NOTIFY stateChanged)
		Q_PROPERTY(QString zip READ zip WRITE setZip NOTIFY zipChanged)
		Q_PROPERTY(QString country READ country WRITE setCountry NOTIFY countryChanged)
		Q_PROPERTY(QString phoneDay READ phoneDay WRITE setPhoneDay NOTIFY phoneDayChanged)
		Q_PROPERTY(QString email READ email WRITE setEmail NOTIFY emailChanged)

		public:
			explicit Member(QObject* parent = nullptr) :
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
				m_email{""},
				m_data{nullptr}
			{}
			~Member() {}

			void logIn(QString const& username, QString const& password,
					QString const& successPage = nullptr,
					QString const& nextPage = nullptr,
					QString const& failPage = nullptr,
					size_t (*handler)(void*, size_t, size_t,
						void*) = nullptr);
			void account(QString const& firstName,
					QString const& lastName,
					QString const& address1,
					QString const& address2,
					QString const& city,
					QString const& state,
					QString const& zip,
					QString const& email,
					QString const& phoneDay) {}
			void changePassword(QString const& passwordOld,
					QString const& password,
					QString const& verify) {}
			void logOut();

			QString const& userName() const { return m_userName; }
			QString const& userNick() const { return m_userNick; }
			QString const& password() const { return m_password; }
			QString const& expiration() const { return m_expiration; }
			QString const& acl() const { return m_acl; }
			QString const& modTime() const { return m_modTime; }
			QString const& sNickName() const { return m_sNickName; }
			QString const& company() const { return m_company; }
			QString const& fName() const { return m_fName; }
			QString const& lName() const { return m_lName; }
			QString const& address1() const { return m_address1; }
			QString const& address2() const { return m_address2; }
			QString const& address3() const { return m_address3; }
			QString const& city() const { return m_city; }
			QString const& state() const { return m_state; }
			QString const& zip() const { return m_zip; }
			QString const& country() const { return m_country; }
			QString const& phoneDay() const { return m_phoneDay; }
			QString const& email() const { return m_email; }

			void setUserName(QString const& userName);
			void setUserNick(QString const& userNick);
			void setPassword(QString const& password);
			void setExpiration(QString const& expiration);
			void setAcl(QString const& acl);
			void setModTime(QString const& modTime);
			void setSNickName(QString const& sNickName);
			void setCompany(QString const& company);
			void setFName(QString const& fName);
			void setLName(QString const& lName);
			void setAddress1(QString const& address1);
			void setAddress2(QString const& address2);
			void setAddress3(QString const& address3);
			void setCity(QString const& city);
			void setState(QString const& state);
			void setZip(QString const& zip);
			void setCountry(QString const& country);
			void setPhoneDay(QString const& phoneDay);
			void setEmail(QString const& email);

		signals:
			void userNameChanged();
			void userNickChanged();
			void passwordChanged();
			void expirationChanged();
			void aclChanged();
			void modTimeChanged();
			void sNickNameChanged();
			void companyChanged();
			void fNameChanged();
			void lNameChanged();
			void address1Changed();
			void address2Changed();
			void address3Changed();
			void cityChanged();
			void stateChanged();
			void zipChanged();
			void countryChanged();
			void phoneDayChanged();
			void emailChanged();

		private:
			QString m_userName;
			QString m_userNick;
			QString m_password;
			QString m_expiration;
			QString m_acl;
			QString m_modTime;
			QString m_sNickName;
			QString m_company;
			QString m_fName;
			QString m_lName;
			QString m_address1;
			QString m_address2;
			QString m_address3;
			QString m_city;
			QString m_state;
			QString m_zip;
			QString m_country;
			QString m_phoneDay;
			QString m_email;
			icclient_member* m_data;
	};

}

#endif // QICCLIENT_MEMBER_HXX
