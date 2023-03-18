#include <interchange.h>
#include <interchange/admin.h>
#include "interchange/admin.hxx"

namespace QInterchange {

	static char *unCopy, *pwCopy, *npCopy, *spCopy, *fpCopy;

	void Admin::logIn(QString const& username, QString const& password,
			QString const& nextPage, QString const& successPage,
			QString const& failPage)
	{
		auto unData = username.toLatin1().constData();
		unCopy = (char*)malloc(strlen(unData) + 1);
		strcpy(unCopy, unData);
		auto pwData = password.toLatin1().constData();
		pwCopy = (char*)malloc(strlen(pwData) + 1);
		strcpy(pwCopy, pwData);
		auto npData = nextPage.toLatin1().constData();
		npCopy = (char*)malloc(strlen(npData) + 1);
		strcpy(npCopy, npData);
		auto spData = successPage.toLatin1().constData();
		spCopy = (char*)malloc(strlen(spData) + 1);
		strcpy(spCopy, spData);
		auto fpData = failPage.toLatin1().constData();
		fpCopy = (char*)malloc(strlen(fpData) + 1);
		strcpy(fpCopy, fpData);
		interchange_admin_login(unCopy, pwCopy, npCopy, spCopy, fpCopy,
				[](interchange_response* response) {
			free(unCopy);
			free(pwCopy);
			free(npCopy);
			free(spCopy);
			free(fpCopy);
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

	void Admin::setData(interchange_admin* data)
	{
		if (data && data->username && m_userName != data->username) {
			m_userName = QString{data->username};
			emit userNameChanged();
		} else setUserName("");

		if (data && data->password && m_password != data->password) {
			m_password = QString{data->password};
			emit passwordChanged();
		} else setPassword("");

		if (data && data->name && m_name != data->name) {
			m_name = QString{data->name};
			emit nameChanged();
		} else setName("");

		if (data) setSuper(data->super);
		else setSuper("");

		if (m_data != data) m_data = data;
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
		interchange_admin_logout(m_data, nullptr);
		setData(nullptr);
	}

}
