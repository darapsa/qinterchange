#include <interchange.h>
#include <interchange/admin.h>
#include "interchange/admin.hxx"

namespace QInterchange {

	static Admin *admin;
	static char *unCopy, *pwCopy, *npCopy, *spCopy, *fpCopy;

	Admin::Admin(QObject *parent) :
		QObject{parent},
		m_userName{""},
		m_password{""},
		m_name{""},
		m_super{false}
	{
		admin = this;
	}

	Admin::Admin(interchange_admin data, QObject *parent) :
		QObject{parent}
	{
		admin = this;

		if (data.username) m_userName = QString{data.username};
		else setUserName("");

		if (data.password) m_password = QString{data.password};
		else setPassword("");

		if (data.name) m_name = QString{data.name};
		else setName("");

		setSuper(data.super);
	}

	void Admin::logIn(QString const& username, QString const& password,
			QString const& nextPage, QString const& successPage,
			QString const& failPage)
	{
		unCopy = (char *)malloc(username.size() + 1);
		strcpy(unCopy, username.toLatin1().constData());
		pwCopy = (char *)malloc(password.size() + 1);
		strcpy(pwCopy, password.toLatin1().constData());
		if (nextPage.isEmpty())
			npCopy = nullptr;
		else {
			npCopy = (char *)malloc(nextPage.size() + 1);
			strcpy(npCopy, nextPage.toLatin1().constData());
		}
		if (successPage.isEmpty())
			spCopy = nullptr;
		else {
			spCopy = (char *)malloc(successPage.size() + 1);
			strcpy(spCopy, successPage.toLatin1().constData());
		}
		if (failPage.isEmpty())
			fpCopy = nullptr;
		else {
			fpCopy = (char *)malloc(failPage.size() + 1);
			strcpy(fpCopy, failPage.toLatin1().constData());
		}
		interchange_admin_login(unCopy, pwCopy, npCopy, spCopy, fpCopy,
				[](interchange_response* response) {
			free(unCopy);
			free(pwCopy);
			if (npCopy) free(npCopy);
			if (spCopy) free(spCopy);
			if (fpCopy) free(fpCopy);
			admin->emitLogin(QString{response->data});
			interchange_free_response(response);
		}, nullptr);
	}

	void Admin::setUserName(QString const& userName)
	{
		if (m_userName != userName) {
			m_userName = userName;
			emit userNameChanged();
		}
	}
	void Admin::setPassword(QString const& password)
	{
		if (m_password != password) {
			m_password = password;
			emit passwordChanged();
		}
	}
	void Admin::setName(QString const& name)
	{
		if (m_name != name) {
			m_name = name;
			emit nameChanged();
		}
	}
	void Admin::setSuper(bool super)
	{
		if (m_super != super) {
			m_super = super;
			emit superChanged();
		}
	}

	void Admin::newAdmin(QString const& userName, QString const& password, QString const& name, bool super,
			enum interchange_admin_group group)
	{
		interchange_admin_new_admin(userName.toLatin1().constData(), password.toLatin1().constData(),
				name.toLatin1().constData(), super, group, nullptr);
	}

	void Admin::newItem(QString const& description, QString const& comment,
			QString const& price, QString const& imagePath)
	{
		interchange_admin_new_item(description.toLatin1().constData(), comment.toLatin1().constData(),
				price.toLatin1().constData(), imagePath.toLatin1().constData(), nullptr);
	}

	void Admin::logOut()
	{
		interchange_admin_logout();
	}

	void Admin::emitLogin(const QString &response)
	{
		emit loggedIn(response);
	}
}
