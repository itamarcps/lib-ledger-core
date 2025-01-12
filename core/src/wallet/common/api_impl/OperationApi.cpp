/*
 *
 * OperationApi
 * ledger-core
 *
 * Created by Pierre Pollastri on 03/07/2017.
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 Ledger
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */
#include "OperationApi.h"
#include <iterator>
#include <wallet/common/Amount.h>
#include <wallet/common/AbstractAccount.hpp>
#include <wallet/cosmos/api_impl/CosmosLikeOperation.hpp>
#include <wallet/bitcoin/api_impl/BitcoinLikeOperation.h>
#include <wallet/ethereum/api_impl/EthereumLikeOperation.h>
#include <wallet/ripple/api_impl/RippleLikeOperation.h>
#include <wallet/tezos/api_impl/TezosLikeOperation.h>
#include <wallet/algorand/operations/AlgorandOperation.hpp>
#include <api/WalletType.hpp>
#include <wallet/stellar/StellarLikeOperation.hpp>

namespace ledger {
    namespace core {

        OperationApi::OperationApi(const std::shared_ptr<AbstractAccount> &account)  : ManagedObject<OperationApi>() {
            _account = account;
        }

        std::string OperationApi::getUid() {
            return _backend.uid;
        }

        int32_t OperationApi::getAccountIndex() {
            return _account->getIndex();
        }

        api::OperationType OperationApi::getOperationType() {
            return _backend.type;
        }

        std::chrono::system_clock::time_point OperationApi::getDate() {
            return _backend.date;
        }

        std::vector<std::string> OperationApi::getSenders() {
            return _backend.senders;
        }

        std::vector<std::string> OperationApi::getRecipients() {
            return _backend.recipients;
        }

        std::vector<std::string> OperationApi::getSelfRecipients() {
            // Depending on the coin, we need extra logic; for most coins, getSelfRecipients is
            // trivial as the keychain contains only one address, but for some coins, like BTC,
            // it’s a bit more complicated (we need to check whether the keychain contains the
            // address.
            //
            // In order to do this, we need to access the account’s keychain and perform the test.
            std::vector<std::string> recipients;

            auto keychain = _account->getAccountKeychain();
            std::copy_if(
                _backend.recipients.cbegin(),
                _backend.recipients.cend(),
                std::back_inserter(recipients),
                [&](std::string const& addr) -> bool
            {
                return keychain->contains(addr);
            });

            return recipients;
        }

        ledger::core::Operation &OperationApi::getBackend() {
            return _backend;
        }

        const ledger::core::Operation &OperationApi::getBackend() const {
            return _backend;
        }

        api::WalletType OperationApi::getWalletType() {
            return _backend.walletType;
        }

        bool OperationApi::isInstanceOfBitcoinLikeOperation() {
            return _backend.walletType == api::WalletType::BITCOIN;
        }

        bool OperationApi::isInstanceOfCosmosLikeOperation() {
            return _backend.walletType == api::WalletType::COSMOS;
        }

        bool OperationApi::isInstanceOfEthereumLikeOperation() {
            return _backend.walletType == api::WalletType::ETHEREUM;
        }

        bool OperationApi::isInstanceOfRippleLikeOperation() {
            return _backend.walletType == api::WalletType::RIPPLE;
        }

        bool OperationApi::isInstanceOfTezosLikeOperation() {
            return _backend.walletType == api::WalletType::TEZOS;
        }

        bool OperationApi::isComplete() {
            if (_backend.walletType == api::WalletType::BITCOIN) {
                return _backend.bitcoinTransaction.nonEmpty();
            } else if (_backend.walletType == api::WalletType::COSMOS) {
                return _backend.cosmosTransaction.nonEmpty();
            } else if (_backend.walletType == api::WalletType::ETHEREUM) {
                return _backend.ethereumTransaction.nonEmpty();
            } else if (_backend.walletType == api::WalletType::RIPPLE) {
                return _backend.rippleTransaction.nonEmpty();
            } else if (_backend.walletType == api::WalletType::TEZOS) {
                return _backend.tezosTransaction.nonEmpty();
            } else if (_backend.walletType == api::WalletType::STELLAR) {
                return _backend.stellarOperation.nonEmpty();
            }
            return false;
        }

        std::shared_ptr<api::TrustIndicator> OperationApi::getTrust() {
            return _backend.trust;
        }

        std::shared_ptr<api::Preferences> OperationApi::getPreferences() {
            return _account->getOperationExternalPreferences(_backend.accountUid);
        }

        optional<int64_t> OperationApi::getBlockHeight() {
            return _backend.block.map<int64_t>([] (const Block& block) {
                return (int64_t) block.height;
            });
        }

        std::shared_ptr<api::Amount> OperationApi::getFees() {
            if (getBackend().fees.nonEmpty())
                return std::make_shared<Amount>(_account->getWallet()->getCurrency(), 0, getBackend().fees.getValue());
            else
                return nullptr;
        }

        std::shared_ptr<api::Amount> OperationApi::getAmount() {
            return std::make_shared<Amount>(_account->getWallet()->getCurrency(), 0, getBackend().amount);
        }

        std::shared_ptr<api::BitcoinLikeOperation> OperationApi::asBitcoinLikeOperation() {
            if (getWalletType() != api::WalletType::BITCOIN) {
                throw make_exception(api::ErrorCode::BAD_CAST, "Operation is not of Bitcoin type.");
            }
            return std::make_shared<BitcoinLikeOperation>(shared_from_this());
        }

        std::shared_ptr<api::CosmosLikeOperation> OperationApi::asCosmosLikeOperation() {
            if (getWalletType() != api::WalletType::COSMOS) {
                throw make_exception(api::ErrorCode::BAD_CAST, "Operation is not of Cosmos type.");
            }
            return std::make_shared<CosmosLikeOperation>(shared_from_this());
        }

        std::shared_ptr<api::EthereumLikeOperation> OperationApi::asEthereumLikeOperation() {
            if (getWalletType() != api::WalletType::ETHEREUM) {
                throw make_exception(api::ErrorCode::BAD_CAST, "Operation is not of Ethereum type.");
            }
            return std::make_shared<EthereumLikeOperation>(shared_from_this());
        }

        std::shared_ptr<api::RippleLikeOperation> OperationApi::asRippleLikeOperation() {
            if (getWalletType() != api::WalletType::RIPPLE) {
                throw make_exception(api::ErrorCode::BAD_CAST, "Operation is not of Ripple type.");
            }
            return std::make_shared<RippleLikeOperation>(shared_from_this());
        }

        std::shared_ptr<api::TezosLikeOperation> OperationApi::asTezosLikeOperation() {
            if (getWalletType() != api::WalletType::TEZOS) {
                throw make_exception(api::ErrorCode::BAD_CAST, "Operation is not of Tezos type.");
            }
            return std::make_shared<TezosLikeOperation>(shared_from_this());
        }

        std::shared_ptr<api::AlgorandOperation> OperationApi::asAlgorandOperation() {
            if (getWalletType() != api::WalletType::ALGORAND) {
                throw make_exception(api::ErrorCode::BAD_CAST, "Operation is not of Algorand type.");
            }
            return std::dynamic_pointer_cast<algorand::Operation>(shared_from_this());
        }

        const std::shared_ptr<AbstractAccount> &OperationApi::getAccount() const {
            return _account;
        }

        api::Currency OperationApi::getCurrency() {
            return _account->getWallet()->getCurrency();
        }

        std::shared_ptr<api::StellarLikeOperation> OperationApi::asStellarLikeOperation() {
            return std::make_shared<StellarLikeOperation>(shared_from_this());
        }

        bool OperationApi::isInstanceOfStellarLikeOperation() const {
            return _backend.walletType == api::WalletType::STELLAR;
        }

    }
}
