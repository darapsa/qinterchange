#ifndef QICCLIENT_ADMIN_HXX
#define QICCLIENT_ADMIN_HXX

#include <QObject>
#include <icclient/typedefs.h>
#include <icclient/admin.h>

struct icclient_admin;

namespace QICClient {

	class Admin : public QObject
	{
		Q_OBJECT
		Q_PROPERTY(QString userName READ userName WRITE setUserName NOTIFY userNameChanged)
		Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)
		Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
		Q_PROPERTY(bool super READ super WRITE setSuper NOTIFY superChanged)

		public:
			explicit Admin(QObject* parent = nullptr) :
				QObject{parent},
				m_userName{""},
				m_password{""},
				m_name{""},
				m_super{false},
				m_data{nullptr}
			{}
			~Admin() {}
			static std::shared_ptr<Admin> logIn(QString const& username,
					QString const& password,
					QString const& successPage = nullptr,
					QString const& nextPage = nullptr,
					QString const& failPage = nullptr,
					void (*handler)(icclient_fetch_t *) = nullptr);

			QString const& userName() const { return m_userName; }
			QString const& password() const { return m_password; }
			QString const& name() const { return m_name; }
			bool super() { return m_super; }

			void setUserName(QString const& userName);
			void setPassword(QString const& password);
			void setName(QString const& name);
			void setSuper(bool super);

		public slots:
			void newAdmin(QString const& userName, QString const& password, QString const& name, bool super,
					enum icclient_admin_group group);
			void newItem(QString const& description, QString const& comment, QString const& price,
					QString const& imagePath);
			void logOut();

		signals:
			void userNameChanged();
			void passwordChanged();
			void nameChanged();
			void superChanged();

		private:
			QString m_userName;
			QString m_password;
			QString m_name;
			bool m_super;
			icclient_admin* m_data;
			inline void setData(icclient_admin* data);
	};

}

#endif // QICCLIENT_ADMIN_HXX
