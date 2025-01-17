/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_VENDOR_BAT_NATIVE_LEDGER_SRC_BAT_LEDGER_INTERNAL_PROMOTION_PROMOTION_H_
#define BRAVE_VENDOR_BAT_NATIVE_LEDGER_SRC_BAT_LEDGER_INTERNAL_PROMOTION_PROMOTION_H_

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "base/timer/timer.h"
#include "bat/ledger/ledger.h"
#include "bat/ledger/mojom_structs.h"
#include "bat/ledger/internal/attestation/attestation_impl.h"
#include "bat/ledger/internal/credentials/credentials_factory.h"
#include "bat/ledger/internal/endpoint/promotion/promotion_server.h"

namespace ledger {
class LedgerImpl;

namespace promotion {

class PromotionTransfer;

class Promotion {
 public:
  explicit Promotion(LedgerImpl* ledger);
  virtual ~Promotion();

  void Initialize();

  void Fetch(ledger::FetchPromotionCallback callback);

  void Claim(
      const std::string& promotion_id,
      const std::string& payload,
      ledger::ClaimPromotionCallback callback);

  void Attest(
      const std::string& promotion_id,
      const std::string& solution,
      ledger::AttestPromotionCallback callback);

  void Refresh(const bool retry_after_error);

  virtual void TransferTokens(ledger::PostSuggestionsClaimCallback callback);

  void GetDrainStatus(const std::string& drain_id,
                      ledger::GetDrainCallback callback);

 private:
  void OnFetch(ledger::FetchPromotionCallback callback,
               type::Result result,
               type::PromotionList list,
               const std::vector<std::string>& corrupted_promotions);

  void OnGetAllPromotions(ledger::FetchPromotionCallback callback,
                          type::PromotionList list,
                          type::PromotionMap promotions);

  void OnGetAllPromotionsFromDatabase(ledger::FetchPromotionCallback callback,
                                      type::PromotionMap promotions);

  void LegacyClaimedSaved(
      const type::Result result,
      std::shared_ptr<type::PromotionPtr> shared_promotion);

  void OnClaimPromotion(ledger::ClaimPromotionCallback callback,
                        const std::string& payload,
                        type::PromotionPtr promotion);

  void OnCreateWalletIfNecessary(ledger::ClaimPromotionCallback callback,
                                 const std::string& payload,
                                 type::Result result);

  void OnAttestPromotion(ledger::AttestPromotionCallback callback,
                         const std::string& solution,
                         type::PromotionPtr promotion);

  void OnAttestedPromotion(ledger::AttestPromotionCallback callback,
                           const std::string& promotion_id,
                           type::Result result);

  void OnCompletedAttestation(ledger::AttestPromotionCallback callback,
                              type::PromotionPtr promotion);

  void AttestedSaved(ledger::AttestPromotionCallback callback,
                     type::PromotionPtr promotion,
                     type::Result result);

  void Complete(ledger::AttestPromotionCallback callback,
                const std::string& promotion_string,
                type::Result result);

  void OnComplete(ledger::AttestPromotionCallback callback,
                  type::Result result,
                  type::PromotionPtr promotion);

  void ProcessFetchedPromotions(
      const type::Result result,
      type::PromotionList promotions,
      ledger::FetchPromotionCallback callback);

  void GetCredentials(ledger::ResultCallback callback,
                      type::PromotionPtr promotion);

  void CredentialsProcessed(ledger::ResultCallback callback,
                            const std::string& promotion_id,
                            type::Result result);

  void Retry(type::PromotionMap promotions);

  void CheckForCorrupted(const type::PromotionMap& promotions);

  void CorruptedPromotionFixed(const type::Result result);

  void CheckForCorruptedCreds(type::CredsBatchList list);

  void CorruptedPromotions(
      type::PromotionList promotions,
      const std::vector<std::string>& ids);

  void OnCheckForCorrupted(
      const type::Result result,
      const std::vector<std::string>& promotion_id_list);

  void ErrorStatusSaved(
      const type::Result result,
      const std::vector<std::string>& promotion_id_list);

  void ErrorCredsStatusSaved(const type::Result result);

  void OnRetryTimerElapsed();

  void OnLastCheckTimerElapsed();

  std::unique_ptr<ledger::attestation::AttestationImpl> attestation_;
  std::unique_ptr<PromotionTransfer> transfer_;
  std::unique_ptr<credential::Credentials> credentials_;
  std::unique_ptr<endpoint::PromotionServer> promotion_server_;
  LedgerImpl* ledger_;  // NOT OWNED
  base::OneShotTimer last_check_timer_;
  base::OneShotTimer retry_timer_;
};

}  // namespace promotion
}  // namespace ledger

#endif  // BRAVE_VENDOR_BAT_NATIVE_LEDGER_SRC_BAT_LEDGER_INTERNAL_PROMOTION_PROMOTION_H_
