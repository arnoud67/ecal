/* ========================= eCAL LICENSE =================================
 *
 * Copyright (C) 2016 - 2019 Continental Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * ========================= eCAL LICENSE =================================
*/

#pragma once

#include <QWidget>
#include "ui_topic_widget.h"
#include <QPoint>

#include <qecalrec.h>

#include "models/topic_list_model.h"

#include <CustomQt/QStableSortFilterProxyModel.h>

class TopicWidget : public QWidget
{
  Q_OBJECT

public:
  TopicWidget(QWidget *parent = Q_NULLPTR);
  ~TopicWidget();

private slots:
  void recordModeChanged(eCAL::rec::RecordMode record_mode);
  void updateRecordModeEnabledStates();
  void topicBlacklistChanged(const std::set<std::string>& blacklist);
  void topicWhitelistChanged(const std::set<std::string>& whitelist);
  void monitorUpdated(const std::map<std::string, eCAL::rec::TopicInfo> topic_info_map);

  void showBlacklistDialog();
  void showWhitelistDialog();
  void updateTopicCounterLabel();

  void treeviewContextMenuRequested(const QPoint& pos);

  void addSelectedTopicsToBlacklist();
  void addSelectedTopicsToWhitelist();
  void removeSelectedTopicsFromBlacklist();
  void removeSelectedTopicsFromWhitelist();
  void copySelectedTopicNames();

private:
  Ui::TopicWidget ui_;

  bool connect_to_ecal_button_state_is_connect_;

  TopicListModel*              blacklist_model_;
  TopicListModel*              whitelist_model_;
  TopicListModel*              all_topics_model_;
  QStableSortFilterProxyModel* topics_hide_disabled_proxy_model_;
  QStableSortFilterProxyModel* topics_user_filter_proxy_model_;

  inline TopicListModel* activeModel() const;

  inline QModelIndex mapToSource  (const QModelIndex& proxy_index) const;
  inline QModelIndex mapFromSource(const QModelIndex& source_index) const;

  QModelIndexList selectedSourceIndexes(int column = 0) const;
  int countListedIndexes(const QModelIndexList& index_list) const;
};
